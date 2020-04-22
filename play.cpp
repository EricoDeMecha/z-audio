#include "player.hpp"

int main(int argc, char **argv)
{
    if(argc  < 2)
    {
        std::cout << "INFO: Audio directory is required" << std::endl;
        return 1;
    }
    const std::string dir = argv[1];
    Player *pl = nullptr;
    contr::slist<std::string> playlist =  pl->generatePlaylist(dir);
    pl->player_init();
    BOOST_FOREACH(auto item, playlist)
                {
                    pl->player(static_cast<const char *>(item.c_str()));
                }

    pl->player_release();
    return 0;
}