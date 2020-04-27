#include "player.hpp"

bool Player::succeedWarn(const std::string &message , FMOD_RESULT result)
{
    if(result != FMOD_OK)
    {
        std::cerr << message << " : "<< result<< " "<< FMOD_ErrorString(result) << std::endl;
        return false;
    }
    return true;
}

void Player::player_init()
{
    std::cout << "Now playing..." << std::endl;
    result = FMOD::System_Create(&system);
    if(!succeedWarn("FMOD:: Failed to create the system object", result))
        //quit
        exit(-1);
    // initialize FMOD
    result = system->init(512, FMOD_INIT_NORMAL, nullptr);
    if(!succeedWarn("FMOD:: Failed to initialize FMOD", result))
        exit(-1);
}
// callback
FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL *channelControl, FMOD_CHANNELCONTROL_TYPE  controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void *commandData1, void *commandData2)
{
    std::cout << "Callback called for " << controlType << std::endl;
    return FMOD_OK;
}
void Player::player(const char *file)
{
    //create the channel group
    result = system->createChannelGroup("Mp3 player", &channelGroup);
    if(!succeedWarn("FMOD:: Failed to create the channel group", result))
        exit(-1);
    // create the sound
    system->createSound(file, FMOD_DEFAULT, nullptr, &sound);

    // play the sound
    result = system->playSound(sound, nullptr, false, &channel);
    if(!succeedWarn("FMOD: Failed to play the sound", result))
        exit(-1);
    // assign the channel to the group
    result = channel->setChannelGroup(channelGroup);
    if(!succeedWarn("FMOD: Failed to assign the channel to the group", result))
        exit(-1);

    // set a callback on the channel
    channel->setCallback(&channelGroupCallback);
    if(!succeedWarn("FMOD: Failed to set the callback for sound", result))
        exit(-1);

    bool isPlaying = false;
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        channel->isPlaying(&isPlaying);
        system->update();
    }while(isPlaying);
}

void Player::player_release()
{
    sound->release();
    channelGroup->release();
    system->release();
}

// --------- Playlist----------------
contr::slist<std::string> Playlist::generatePlaylist(const std::string& dir_name)
{
    contr::slist<std::string> playlist;
    try
    {
        // adding elements after
        contr::slist<std::string>::iterator  last = playlist.before_begin();
        /*
         * later we will use
         * playlist.emplace_after(last, item);
         * ++last;
         * */
        if(!fs::exists(dir_name) || !fs::is_directory(dir_name))
            exit(-1);
        fs::directory_iterator dirit(dir_name),end;

        std::for_each(dirit , end , [playlist,last](const fs::directory_entry& entry)mutable{

            playlist.emplace_after(last,entry.path().string());
            ++last;

        });
    }
    catch(std::exception& e)
    {
        std::cout << "Exception Thrown: " << e.what() << std::endl;
    }

    std::cout << "---Playlist---" << std::endl;
    BOOST_FOREACH(auto item, playlist)
    {
        std::cout << item << std::endl;
    }

    return playlist;
}
