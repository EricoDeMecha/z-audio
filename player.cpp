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
key::keyFlag Player::player(const char *file)
{
    //create the channel group
    result = system->createChannelGroup( "Mp3 Player" , &channelGroup);
    if(!succeedWarn("FMOD:: Failed to create the channel group", result))
        exit(-1);
    std::cout << "[Debug] Creating Sound " << std::endl;
    // create the sound
    system->createSound(file, FMOD_DEFAULT, nullptr, &sound);
    std::cout << "[Debug] Playing Sound " << std::endl;
    // play the sound
    result = system->playSound(sound, nullptr, false, &channel);
    if(!succeedWarn("FMOD: Failed to play the sound", result))
        exit(-1);
    std::cout << "[Debug] setting the channel " << std::endl;
    // assign the channel to the group
    result = channel->setChannelGroup(channelGroup);
    if(!succeedWarn("FMOD: Failed to assign the channel to the group", result))
        exit(-1);
    std::cout << "[Debug] Beginning the callback" << std::endl;
    // set a callback on the channel
    channel->setCallback(&channelGroupCallback);
    if(!succeedWarn("FMOD: Failed to set the callback for sound", result))
        exit(-1);
    std::cout << "[Debug] Status... " << std::endl;
    bool isPlaying = false;
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        channel->isPlaying(&isPlaying);
        system->update();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
        {
            channelGroup->stop();
            return  key::FORWARD;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
        {
            channelGroup->stop();
            return key::BACK;
        } else{
            continue;
        }
    }while(isPlaying);
    return key::OK;
}

void Player::player_release()
{
    sound->release();
    channelGroup->release();
    system->release();
}

// --------- Playlist----------------
contr::stable_vector<std::string> Playlist::generatePlaylist(const std::string& dir_name)
{
    contr::stable_vector<std::string> playlist;
    try
    {
        if(!fs::exists(dir_name) || !fs::is_directory(dir_name))
            exit(-1);
        fs::directory_iterator dirit(dir_name),end;

        std::for_each(dirit , end , [&playlist](const fs::directory_entry& entry){
            playlist.push_back(entry.path().string());
        });
    }
    catch(std::exception& e)
    {
        std::cout << "Exception Thrown: " << e.what() << std::endl;
    }

    std::cout << "---Playlist---" << std::endl;
    for(size_t  i = 0; i < playlist.capacity() ; i++)
    {
        std::cout << playlist[i] << std::endl;
    }
    return playlist;
}
