#include "definitions_include.h"

projectile projectile::create_projectile(const translational& pos, const float& speed, point2d<float> direction)
{
    return projectile(
        game_object::create_game_object(
            vector<string>{in_cur_dir(R"(\sprites_data\projectiles\projectile.png)")},
            pos),
        speed,
        direction
    );
}

void projectile::move(const float& left_bound, const float& right_bound)
{
    teleport_on_bounds(left_bound, right_bound);

    translational::move({direction_ * move_speed_});
}
