#pragma once
#include "declarations.h"

/// <summary>
/// 
/// Class drawable stores sprites.
/// Gives ability to draw and modify them.
/// 
/// </summary>
class drawable
{
	sprite_pointer skin_ = nullptr;

	int skin_width_ = 0;
	int skin_height_ = 0;


	// i know this is a bad solution, 
	// i do this just bcs there are no copy constructor(which is actually really sad)

	// i tried using vector to store sprite_pointer 
	// and the vector of int that stored the quantity of objects that use the pointers
	// but... compiler decided to cause me headaches...
	string skin_path_ = "";
public:

	sprite_pointer get_skin()const { return skin_; }

	bool is_skin_empty()const { return skin_ == nullptr; }

	int get_width() const { return skin_width_; }
	int get_height() const { return skin_height_; }
	bool set_size(const width_height& size_in);

	bool get_size(width_height& size_out) const;

	bool draw(const translational& location) const;
	bool draw(const point2d<float>& location) const;
	// another example of dirty coding in this method
	drawable& operator= (const drawable& other);

	drawable& operator= (drawable&& other) noexcept;

	static drawable create_drawable(const string& path);
	static vector<drawable> create_drawables(const vector<string>& paths);
	static vector<drawable> create_drawables(const string& txt_path);




	drawable() = default;



	// copy constructor - here is where I start to be a really dirty coder :)
	drawable(const drawable& other)
		: skin_path_(other.skin_path_),
		skin_width_(other.skin_width_),
		skin_height_(other.skin_height_)
	{
		string real_path = other.skin_path_;
		skin_ = createSprite(real_path.c_str());
	}

	drawable(drawable&& other) noexcept {
		skin_ = other.skin_;
		skin_path_ = other.skin_path_;
		skin_width_ = other.skin_width_;
		skin_height_ = other.skin_height_;

		other.skin_ = nullptr;
		other.skin_path_ = "";
		other.skin_width_ = 0;
		other.skin_height_ = 0;


	}



	drawable(const sprite_pointer& skin_, const int& width, const int& height, const string& skin_path_)
		: skin_(skin_), skin_width_(width), skin_height_(height), skin_path_(skin_path_)
	{
	}
	~drawable()
	{
		if (!is_skin_empty())
			destroySprite(skin_);
	}
};

