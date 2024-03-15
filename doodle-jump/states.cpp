#include "definitions_include.h"

drawable states::get_drawable(const int& st) const
{
	if (is_state_ok(st))
		return pictures_[st];
	return drawable();
}

void states::draw(const translational& pos) const
{
	if (is_state_ok())
		pictures_[current_state_].draw(pos);
}

void states::draw_state(const point2d<float>& pos, const int& skin_index_) const
{
	if (is_state_ok(skin_index_))
		pictures_[skin_index_].draw(translational{ pos });
}

int states::width() const
{
	if (is_state_ok())
		return pictures_[current_state_].get_width();
	return 0;
}

int states::height() const
{
	if (is_state_ok())
		return pictures_[current_state_].get_height();
	return 0;
}

void states::scale(const float& scale_x, const float& scale_y)
{
	for (auto& skin : pictures_) {
		int h = skin.get_height();
		int w = skin.get_width();
		skin.set_size(width_height{ (int)(w * scale_x), (int)(h * scale_y) });
	}
}

void states::set_size(const int& width, const int& height)
{
	for (auto& skin : pictures_)
		skin.set_size(width_height{ width, height });

}

states states::create_states(const vector<string>& paths)
{
	return states(drawable::create_drawables(paths));
}

states states::create_states(const string& txt_path)
{
	return states(drawable::create_drawables(txt_path));
}

states states::create_states(const string& txt_path, const int& st)
{
	return states(drawable::create_drawables(txt_path), st);
}
