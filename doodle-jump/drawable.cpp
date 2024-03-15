#include "definitions_include.h"


bool drawable::set_size(const width_height& size_in)
{
	if (is_skin_empty())
		return false;

	setSpriteSize(skin_, size_in.x_, size_in.y_);

	skin_width_ = size_in.x_;
	skin_height_ = size_in.y_;

	return true;
}

bool drawable::get_size(width_height& size_out)const
{
	if (is_skin_empty())
		return false;

	size_out.x_ = skin_width_;
	size_out.y_ = skin_height_;
	return true;
}

bool drawable::draw(const translational& location) const
{
	if (is_skin_empty())
		return false;

	drawSprite(skin_, (int)(location.get_position().x_), (int)(location.get_position().y_));
	return true;
}
bool drawable::draw(const point2d<float>& location) const
{
	if (is_skin_empty())
		return false;

	drawSprite(skin_, (int)(location.x_), (int)(location.y_));
	return true;
}
drawable drawable::create_drawable(const string& path)
{

	string real_path = path;
	ifstream check_exist(real_path);

	if (!check_exist)
		return drawable{};
	
	sprite_pointer ptr = createSprite(real_path.c_str());

	int width = 0, height = 0;
	getSpriteSize(ptr, width, height);

	return drawable{ ptr, width, height, path };
}

vector<drawable> drawable::create_drawables(const vector<string>& paths)
{
	if (!paths.empty()) {


		vector<drawable>result{ paths.size() };

		for (size_t i = 0; i < paths.size(); i++)
#ifdef _CONSOLE_DEBUG
		{
			// I had "libpng warning: bKGD: invalid",
			// so I had to debug where this error appears
			cout << "Loaded: " << paths[i]<< endl;
#endif // _CONSOLE_DEBUG
			result[i] = create_drawable(paths[i]);
#ifdef _CONSOLE_DEBUG
		}
#endif // _CONSOLE_DEBUG

		return result;
	}
	return vector<drawable>();
}

vector<drawable> drawable::create_drawables(const string & txt_path)
{
	return create_drawables(load_paths_from_txt(txt_path));
}

drawable& drawable::operator=(const drawable& other)
{
	// such a dirty trick EEWWWWWWWWW  :)
	this->skin_path_ = other.skin_path_;
	string real_path = other.skin_path_;
	this->skin_ = createSprite(real_path.c_str());
	this->skin_width_ = other.skin_width_;
	this->skin_height_ = other.skin_height_;
	return *this;
}
drawable& drawable::operator=(drawable&& other) noexcept
{
	skin_ = other.skin_;
	skin_path_ = other.skin_path_;
	this->skin_width_ = other.skin_width_;
	this->skin_height_ = other.skin_height_;
	other.skin_ = nullptr;
	other.skin_path_ = "";
	other.skin_width_ = 0;
	other.skin_height_ = 0;
	return *this;
}