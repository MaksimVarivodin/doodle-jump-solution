#pragma once
#include "declarations.h"
#include "character.h"
#include "game_object.h"
#include "platform.h"
#include "frame_rate.h"
#include "game_text.h"
#include "game_view.h"

class game_environment
{


	bool initialized_ = false;

	bool is_game_over_ = false;
	bool is_game_started_ = false;

	bool bullet_alive_ = false;
	bool monster_alive_ = false;
	bool rocket_alive_ = false;
	bool doodle_under_ability_ = false;

	float left_border_ = 0.f;
	float right_border_ = 0.f;

	int size_x_ = 0;

	int size_y_ = 0;

	int height_score_ = 0;

	int platforms_score_ = 0;

	int enemy_score_ = 0;

	character doodle_ = {};

	enemy monster_ = {};

	rocket rocket_ = {};

	game_object background_ = {};

	vector<platform> plats_ = {};

	projectile bullet_ = {};

	game_text text_renderer_ = {};

	drawable heart_ = {};

	game_view view_to_game_ = {};

	frame_rate frames_per_sec_ = {};
	void set_to_defaults();

	void set_height_score();


	void load_view();
	void load_heart();
	void load_background();
	void load_platform(platform& plat);
	void load_platforms(const float& jump_height);
	void load_text_renderer();
	void load_game_character(const float& jump_height);
	void load_enemy();
	void load_bullet();
	void load_rocket();


	int platforms_under_camera(const float& bottom);
	int find_not_fake_platform();
	void calculate_platform(platform& plat, int& current_height, const int& jump_height);
	void recalculate_platforms(const float& bottom);

	bool doodle_touch_enemy_top();
	bool doodle_touch_enemy();
	bool doodle_touch_rocket();
	void spawn_doodle_after_death();
	void check_doodle_fell_off_platform();



	void launch_projectile(const point2d<float>& position, const point2d<float>& direction);
	bool projectile_above_camera();

	bool enemy_under_camera();

	void generate_platforms(vector<platform>& l, int current_height);
	int generate_enemy_on_initialize();
	void generate_rocket_on_initialize(const int& enemy_index);
	void generate_enemy_on_game();
	void generate_rocket_on_game();
	void generate_enemy(const int& platform_index);
	void generate_rocket(const int& platform_index);


	void change_doodle_on_tick();
	void rocket_change_doodle_on_tick();
	void change_projectile_on_tick();
	void change_enemy_on_tick();


	void check_game_over();

public:

	void move_right(const bool& val = true) { doodle_.set_move_right(val); }
	void move_left(const bool& val = true) { doodle_.set_move_left(val); }
	void shoot(const point2d<float>& mouse_position);

	bool is_initialized() const { return initialized_; }

	void change_on_tick();
	void draw() const;
	void initialize(const int size_x_, const int size_y_, const float& jump_height);
	void re_init();
	void stop_threads() { frames_per_sec_.stop(); }

	game_environment() = default;
};

