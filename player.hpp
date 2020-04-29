#include <iostream>
#include <string>
#include <cassert>

#include <thread>
#include <chrono>

#include <boost/container/slist.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/container/stable_vector.hpp>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "SFML/Window/Keyboard.hpp"


// -----------Playlist----------

namespace contr = boost::container;
namespace fs  = boost::filesystem;

namespace key
{
    enum keyFlag
    {
        OK,
        FORWARD,
        BACK
    };
}
class Playlist
{
public:
    static contr::stable_vector<std::string> generatePlaylist(const std::string&);
};


// ------------Player----------
class Player : public Playlist
{
    FMOD_RESULT result;// status
    // create the main system object
    FMOD::System *system;
    FMOD::ChannelGroup *channelGroup;
    FMOD::Sound *sound;
    FMOD::Channel *channel;
public:
    Player()
    {
        result = FMOD_OK;
        system = nullptr;
        channelGroup = nullptr;
        sound = nullptr;
        channel = nullptr;
    }
    static bool succeedWarn(const std::string &message , FMOD_RESULT result);
    void player_init();
    key::keyFlag player(const char *);
    void player_release();
};