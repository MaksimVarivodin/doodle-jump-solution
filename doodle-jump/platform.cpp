#include "definitions_include.h"

platform& platform:: copy_non_drawable(const platform& other)
{
    set_translational(other);
    set_fake(other.get_fake());
    set_state(other.get_state());
    return *this;
}
bool platform::generate_fake()
{
    int number = 0;
    for(int i =0; i< 3; i++){
        number = generate_random<int>(0, 1);
        if (number!= generate_random<int>(0, 1))
            return false;
    }
    return  true;
}
platform platform::create_platform( const translational & pos, const bool & get_fake)
{
    return platform(game_object::create_game_object("\\sprites_data\\platform.txt", pos), get_fake);
}
