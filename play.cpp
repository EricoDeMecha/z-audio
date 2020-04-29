#include "player.hpp"

int main(int argc, char **argv)
{
    fs::path r_path("audioSample/");
    std::string dir = argc < 2 ? fs::absolute(r_path).string() : argv[1];
    std::cout  << dir << std::endl;
    Player pl;
    contr::stable_vector<std::string> playlist =  Player::generatePlaylist(dir);
    pl.player_init();
    for(size_t i = 0; i < playlist.size(); i++)
    {
        key::keyFlag state = pl.player(static_cast<const char *>(playlist[i].c_str()));
        if(state == key::OK)
        {
            continue;
        }
        else if(state == key::FORWARD)
        {
            continue;
        }
        else if(state == key::BACK)
        {
            if(i != 0)
            {
                i = i - 2;
            }
            else
            {
                i = 0;
            }
        }
    }
    pl.player_release();
    return 0;
}