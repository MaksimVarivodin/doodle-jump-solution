#pragma once
#include "declarations.h"
#include "game_object.h"


class platform : public game_object
{
	bool is_fake_;

public:

	bool get_fake() const {return is_fake_;}
	void set_fake(const bool & fake_){is_fake_ = fake_;};

	platform&  copy_non_drawable(const platform& other);

	static bool generate_fake();

	static platform create_platform(const translational & pos, const bool & get_fake);

	platform(const game_object& obj,const bool & get_fake)
	: game_object::game_object(obj), is_fake_(get_fake)
	{
	}
	platform():game_object::game_object{}, is_fake_(false){}
};

