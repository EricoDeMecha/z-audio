#include <iostream>
#include <string>
#include <cassert>

#include <thread>
#include <chrono>

#include <boost/container/slist.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <fmod.hpp>
#include <fmod_errors.h>


// -----------Playlist----------

namespace contr = boost::container;
namespace fs  = boost::filesystem;

class Playlist
{
public:
    contr::slist<std::string> generatePlaylist(const std::string);
};


// ------------Player----------
class Player : public Playlist
{
    FMOD_RESULT result;// status
    // create the main system object
    FMOD::System *system = nullptr;
    FMOD::ChannelGroup *channelGroup = nullptr;
    FMOD::Sound *sound = nullptr;
    FMOD::Channel *channel = nullptr;
public:
    bool succeedWarn(const std::string &message , FMOD_RESULT result);
    void player_init();
    void player(const char *);
    void player_release();
};