#pragma once
#include "declarations.h"
#include "game_object.h"

class enemy: public game_object
{
	int hp_;
public:

	int get_hp()const{return hp_;}
	void set_hp(const int & hp){hp_ = hp;}
	bool is_alive() const {return hp_ > 0;}

	void cause_damage() {hp_--;}

	static enemy create_enemy(const translational & pos, const int& hp);


	enemy(const game_object& obj,const int & hp)
		: game_object::game_object(obj), hp_(hp)
	{}
	enemy():game_object::game_object{}, hp_(0){}
};

