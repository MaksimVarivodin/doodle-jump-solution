#include "definitions_include.h"

enemy enemy::create_enemy(const translational& pos, const int& hp)
{
    return enemy(game_object::create_game_object(R"(\sprites_data\enemy.txt)", pos), hp);
}
