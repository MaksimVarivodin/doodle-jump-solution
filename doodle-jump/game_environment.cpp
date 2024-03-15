#include "definitions_include.h"



void game_environment::load_view()
{
	view_to_game_ = game_view::create_view(
#ifdef _CAMERA_DEBUG
		drawable::create_drawable(in_cur_dir(R"(\sprites_data\camera_frame.png)")),
#endif // 
		{ 0, 0 },
		{ size_x_, size_y_ },
		{ 1.f, 1.f },
		{ false, true }
	);
}

void game_environment::load_heart()
{
	heart_ = drawable::create_drawable(in_cur_dir(R"(\sprites_data\heart.png)"));
}

void game_environment::load_background()
{
	this->background_ = game_object::create_game_object("\\sprites_data\\background.txt", { {0, 0} });
}

void game_environment::load_platforms(const float& jump_height)
{
	this->plats_.resize(20);

	int current_height = 0;

	generate_platforms(plats_, current_height);

	int index = generate_enemy_on_initialize();
	generate_rocket_on_initialize(index);
}

void game_environment::load_text_renderer()
{
	this->text_renderer_ = game_text::create_game_text();
}

void game_environment::load_game_character(const float& jump_height)
{
	if (size_x_ != 0 && plats_.size() > 0) {

		translational first_plat_pos{ {plats_.front().left(), plats_.front().top()} };
		doodle_ = character::create_character(
			R"(\sprites_data\doodle.txt)",
			first_plat_pos,
			jump_height);

		left_border_ = -(doodle_.width() / 4.f);
		right_border_ = size_x_ + left_border_;
	}

}

void game_environment::load_enemy()
{
	monster_ = enemy::create_enemy({ {} }, 0);
}

void game_environment::load_bullet()
{
	bullet_ = projectile::create_projectile({ {} }, 5.f, {});
}

void game_environment::load_rocket()
{
	rocket_ = rocket::create_rocket({ {} }, doodle_.get_jump_height() * 5.f);
}

void game_environment::load_platform(platform& plat)
{
	plat = platform::create_platform({ {0, 0} }, false);
	plat.set_state(platform_skins::USUAl);
}

void game_environment::initialize(const int size_x_, const int size_y_, const float& jump_height)
{
	this->size_x_ = size_x_;
	this->size_y_ = size_y_;

	frames_per_sec_.launch();

	load_view();

	load_rocket();

	load_enemy();

	load_heart();

	load_bullet();

	load_background();

	load_platforms(jump_height);

	load_text_renderer();
	load_game_character(jump_height);


	is_game_started_ = true;
	initialized_ = true;

}
void game_environment::re_init() {
	set_to_defaults();
	initialize(size_x_, size_y_, (float)(doodle_.get_jump_height()));
}

int game_environment::generate_enemy_on_initialize()
{
	size_t platform_index = plats_.size() - 1;

	while (plats_[platform_index].get_fake() == true)
	{
		platform_index++;
		if (platform_index == plats_.size())
			platform_index = 0;
	}

	generate_enemy((int)platform_index);
	return (int)platform_index;
}

void game_environment::generate_rocket_on_initialize(const int& enemy_index)
{
	size_t rocket_index = enemy_index;
	while (enemy_index == rocket_index || plats_[rocket_index].get_fake() == true)
		rocket_index = generate_random<size_t>(plats_.size() / 2, plats_.size() - 1);
	generate_rocket((int)rocket_index);


}

void game_environment::generate_enemy_on_game()
{
	if (!monster_alive_) {
		bool generate_monster = generate_random<size_t>(0, plats_.size() - 1);
		if (generate_monster)
			generate_enemy((int)(plats_.size() - 1));
	}


}

void game_environment::generate_rocket_on_game()
{
	if (enemy_score_ == 5)
	{
		enemy_score_ = 0;
		if (!rocket_alive_ && !doodle_under_ability_)
			generate_rocket((int)(plats_.size() - 1));

	}
}

void game_environment::generate_enemy(const int& platform_index)
{
	int hp = generate_random<int>(1, enemy_kinds::ENEMY_COUNT);
	monster_.set_state(hp - 1);
	int platform_width = plats_[platform_index].width() / 2;
	int monster_width = monster_.width() / 2;
	// puts moster on center of platform
	int x_position = plats_[platform_index].left() + platform_width - monster_width;
	monster_.set_position({ x_position,plats_[platform_index].top() });
	monster_alive_ = true;
}

void game_environment::generate_rocket(const int& platform_index)
{

	int platform_width = plats_[platform_index].width() / 2;
	int rocket_width = rocket_.width() / 2;
	// puts rocket on center of platform
	int x_position = plats_[platform_index].left() + platform_width - rocket_width;
	rocket_.set_position({ x_position,plats_[platform_index].top() });
	rocket_alive_ = true;
}



void game_environment::launch_projectile(const point2d<float>& position, const point2d<float>& direction)
{
	bullet_alive_ = true;

	bullet_.set_position(position);
	bullet_.set_move_direction(direction);
	bullet_.set_move_speed(10.f);
}

void game_environment::set_to_defaults()
{

	initialized_ = false;

	is_game_over_ = false;
	is_game_started_ = false;

	bullet_alive_ = false;
	monster_alive_ = false;
	rocket_alive_ = false;
	doodle_under_ability_ = false;

	left_border_ = 0.f;
	right_border_ = 0.f;

	height_score_ = 0;

	platforms_score_ = 0;

	enemy_score_ = 0;

	monster_ = {};

	rocket_ = {};

	background_ = {};

	plats_ = {};

	bullet_ = {};

	text_renderer_ = {};

	heart_ = {};

	view_to_game_ = {};

	frames_per_sec_.stop();

}
void game_environment::set_height_score()
{
	for (auto it = plats_.rbegin(); it != plats_.rend(); ++it)
		if (doodle_.check_movement_direction(*it, it->get_fake()))
			this->height_score_ = it->get_position().y_;

}

int game_environment::platforms_under_camera(const float& bottom)
{

	int i = 0;
	while (i < plats_.size() && plats_[i].get_position().y_ <= bottom)
		i++;
	return i;
}

bool game_environment::projectile_above_camera()
{
	if (bullet_alive_)
		return view_to_game_.object_above_camera(bullet_);
	return true;
}



bool game_environment::enemy_under_camera()
{
	if (monster_alive_)
		return view_to_game_.object_under_camera(monster_);
	return true;
}



void game_environment::recalculate_platforms(const float& bottom)
{
	int current_height = plats_.rbegin()->get_position().y_;
	int plats_under_cam = platforms_under_camera(bottom + plats_.front().height() / 4.f);
	int length = (int)(plats_.size() - plats_under_cam);

	int fake_count = 0;

	for (int i = 0; i < length; i++) {
		plats_[i].copy_non_drawable(plats_[i + plats_under_cam]);

	}



	for (int i = length; i < plats_.size(); i++) {
		calculate_platform(plats_[i], current_height, doodle_.get_jump_height());
		if (plats_[i - 1].get_fake())
			fake_count++;
		if (fake_count >= 1)
		{
			plats_[i].set_fake(false);
			plats_[i].set_state(platform_skins::USUAl);
			fake_count = 0;
		}
#ifdef _PLAT_DEBUG
		if (plats_[i].get_fake())
			cout << "generared : " << i << " f: " << plats_[i].get_fake() << "\t";
#endif // _PLAT_DEBUG

	}


	this->platforms_score_ += plats_under_cam;
}

void game_environment::check_game_over()
{
	is_game_over_ = !doodle_.are_lifes_left();

}

bool game_environment::doodle_touch_enemy_top()
{
	return doodle_.touches_other_objects_top(monster_);
}

bool game_environment::doodle_touch_enemy()
{
	return doodle_.touches(monster_) && monster_alive_;
}

bool game_environment::doodle_touch_rocket()
{
	if (!doodle_under_ability_)
		return doodle_.touches(rocket_);
	return false;
}

void game_environment::spawn_doodle_after_death()
{
	int iter = find_not_fake_platform();
	doodle_.set_position({ plats_[iter].left(), plats_[iter].top() });
}

void game_environment::check_doodle_fell_off_platform()
{
	if (plats_.front().bottom() > doodle_.top()) {
		doodle_.die();
		spawn_doodle_after_death();
	}
}



void game_environment::generate_platforms(vector<platform>& l, int current_height) {
	for (int i = 0; i < l.size(); i++)
	{
		load_platform(plats_[i]);
		calculate_platform(plats_[i], current_height, doodle_.get_jump_height());
	}
}

int game_environment::find_not_fake_platform()
{
	for (int i = 0; i < plats_.size(); i++)
		if (!plats_[i].get_fake())
			return i;
	return -1;
}

void game_environment::calculate_platform(platform& plat, int& current_height, const int& jump_height)
{
	int current_max_height = current_height + jump_height / 2.5f;

	current_height = generate_random<int>(current_height + plat.height(), current_max_height);

	plat.set_position(
		{
		(float)generate_random<int>(0, size_x_ - plat.width()),
		(float)current_height
		});
	current_height += plat.height();

	if (platform::generate_fake()) {
		plat.set_state(platform_skins::FAKE1);
		plat.set_fake(true);
	}
}






void game_environment::shoot(const point2d<float>& mouse_position)
{
	point2d<float> mouse_world_pos = view_to_game_.screen_object_to_world(mouse_position);
	mouse_world_pos.y_ = doodle_.top() + 100.f;
	point2d<float> start_position{ doodle_.get_position().x_ + doodle_.width() / 2, doodle_.top() };
	point2d<float> direction = start_position;
	direction.to_vector(mouse_world_pos).normalize();

	launch_projectile(start_position, direction);

}





void game_environment::change_enemy_on_tick()
{
	monster_alive_ = !enemy_under_camera();
	if (monster_alive_)
	{
		if (bullet_.touches(monster_)) {
			monster_.cause_damage();
			monster_alive_ = monster_.is_alive();
			if (!monster_alive_)
				enemy_score_++;
			bullet_alive_ = false;
		}

	}
}

void game_environment::change_projectile_on_tick()
{
	bullet_alive_ = !projectile_above_camera();
	if (bullet_alive_)
		bullet_.move(left_border_, right_border_);
	else {
		bullet_.set_move_speed(0.f);
		bullet_.set_move_direction({});
	}


}

void game_environment::change_doodle_on_tick()
{
	check_doodle_fell_off_platform();

	doodle_.move_x(left_border_, right_border_);

	doodle_.move_y(frames_per_sec_.get_elapsed_time());

	if (doodle_touch_enemy_top()) {
		monster_alive_ = false;
		enemy_score_++;
	}

	else if (doodle_touch_enemy())
	{
		doodle_.die();
		spawn_doodle_after_death();
	}
	else if (doodle_touch_rocket()) {
		rocket_.set_under_ability(doodle_);
		doodle_under_ability_ = true;
		rocket_alive_ = false;
	}
}

void game_environment::rocket_change_doodle_on_tick()
{
	rocket_.move_doodle_x(doodle_, left_border_, right_border_);
	rocket_.move_doodle_y(doodle_, frames_per_sec_.get_elapsed_time());
	if (rocket_.ability_finished())
	{
		rocket_.set_ability_finished(doodle_, plats_[find_not_fake_platform()]);
		doodle_under_ability_ = false;

		spawn_doodle_after_death();
	}
}

void game_environment::change_on_tick()
{
	check_game_over();
	if (is_initialized() && !is_game_over_ && is_game_started_) {
		if (doodle_under_ability_)
			rocket_change_doodle_on_tick();
		else {

			change_projectile_on_tick();

			change_enemy_on_tick();

			change_doodle_on_tick();

			set_height_score();

			generate_enemy_on_game();

			generate_rocket_on_game();
		}


		if (view_to_game_.follow(doodle_) > 0.f)
			recalculate_platforms(view_to_game_.get_world_bottom());




		frames_per_sec_++;
	}

}


void game_environment::draw() const
{
	if (is_initialized() && !is_game_over_ && is_game_started_) {
		this->background_.draw();
#ifdef _CAMERA_DEBUG
		this->view_to_game_.draw_camera_frame();
#endif // 
		for (const auto& pl : plats_)
			this->view_to_game_.draw(pl);



		if (bullet_alive_)
			this->view_to_game_.draw(this->bullet_);
		if (monster_alive_)
			this->view_to_game_.draw(this->monster_);

		this->view_to_game_.draw(this->doodle_);

		if (rocket_alive_)
			this->view_to_game_.draw(this->rocket_);


		point2d<float> temp = { size_x_ - 100, 20 };
		temp = text_renderer_.draw_text(to_string(doodle_.get_lifes()), temp);

		heart_.draw(temp);

		text_renderer_.draw_text("FPS: " + to_string(frames_per_sec_.get_average_frame_rate()), { 10, 10 });
		text_renderer_.draw_text("Score: " + to_string(height_score_), { 10, 40 });
		text_renderer_.draw_text("Platforms: " + to_string(platforms_score_), { 10, 70 });
		text_renderer_.draw_text("Enemies killed: " + to_string(enemy_score_), { 10, 110 });

	}
	else if (is_initialized())
	{
		this->background_.draw();
		text_renderer_.draw_text("YOU LOST!", { size_x_ / 2 - 100, size_y_ / 2 });
		text_renderer_.draw_text("Right-click to restart!", { size_x_ / 2 - 100, size_y_ / 2 + 100 });
	}

}



