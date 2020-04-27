#include "player.hpp"

int main(int argc, char **argv)
{
    fs::path r_path("audioSample/");
    std::string dir = argc < 2 ? fs::absolute(r_path).string() : argv[1];
    std::cout  << dir << std::endl;
    Player pl;
    contr::slist<std::string> playlist =  Player::generatePlaylist(dir);
    pl.player_init();
    BOOST_FOREACH(auto item, playlist)
                {
                    pl.player(static_cast<const char *>(item.c_str()));
                }

    pl.player_release();
    return 0;
}