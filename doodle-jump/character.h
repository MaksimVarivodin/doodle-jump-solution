#pragma once
#include "declarations.h"
#include "game_object.h"
#include "game_text.h"
#include "rocket.h"
class character: public game_object
{
	friend class rocket;



	float jump_beginning_ = 512.f;
	float jump_height_ = 200.f;
	float move_y_ = 350.f;
	float move_x_ = 3.f;

	bool move_right_ = false;
	bool move_left_ = false;

	// these don't depend on outer logic, 
	// I won't pass them to the constructor
	float acceleration_x_ = 0;
	float acceleration_y_ = 0;
	bool move_up_ = true;
	int lifes_ = 5;
	bool look_left_ = true;
	bool look_right_ = false;

	

	void stand();
	void sit();
	void set_move_up(const float& position);
	void set_move_down();
public:
	 


	void die(){ lifes_--; }
	int get_lifes() const{return lifes_;}
	bool are_lifes_left() const {return lifes_ > 0;}

	void set_move_left(const bool & left = true);
	void set_move_right(const bool & right = true);
	bool check_movement_direction( const game_object& plat, const bool& get_fake);
	void move_x(
		const float& left_bound,
		const float & right_bound);
	void move_y(const float& elapsed_time);
	
	
	int get_jump_height() const {return (int)jump_height_;}


	static character create_character(
		const string& txt_path,
		const translational& pos,
		const float& jump_height);



	character(
		const game_object& obj,	
		const float & jump_height,
		const float & jump_beginning,
		const float & move_y, 
		const float & move_x)
		: game_object::game_object(obj),
		jump_height_(jump_height),
		jump_beginning_(jump_beginning),
		move_y_(move_y), 
		move_x_(move_x)
	{
	}
	character(const game_object& obj)
		: game_object::game_object(obj)
	{
	}
	character() :character(game_object{}) {}



	// rule of five and rule of zero )))
	~character() = default;
	character(const character& other) = default;
	character(character && other) = default;
	character& operator= (const character& other) = default;
	character& operator= (character && other) = default;

	
	
};

