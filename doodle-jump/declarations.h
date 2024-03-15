#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4244 ) 

#ifndef NOMINMAX
# define NOMINMAX
#endif

/*/#define _CONSOLE_DEBUG/**/
/*/#define _CAMERA_DEBUG/**/
/*/#define _PLAT_DEBUG/**/


#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <Windows.h>
#include "Framework.h"
using namespace std;


/*
	Here declarations of all classes used in project.
	I decided to do it this way for easier usability in implementations.
	(when using types from other headers in specific header you don't need to include them,
	e.g. you create "horse" in "horse.h" and you need "movable" from "movable.h",
	if class "movable" is here you can use it in "horse.h", just include "header.h")

	Also it helps to manage project, go to definitions, etc.

	In addition, I have created "link_implementations.h" header file.
	This one is including all headers, so that I can easily implement the methods which not rarely have types from other headers.
	So this one keeps control of included headers, so that i don't need to manage order of included headers in each header.
	For example,
	instead of :

	// header1.h
	// some code

	// header2.h
	// #include "header1.h"
	// some code

	// header3.h
	// #include "header2.h"
	// some code

	// source1.cpp
	// #include "header1.h"
	// some code

	// source2.cpp
	// #include "header2.h"
	// some code

	// source3.cpp
	// #include "header3.h"
	// some code

	i have :

	// header_declarations.h
	// all declarations

	// camera.h, movable.h...
	// header files with definitions

	// definitions_include.h
	// bunch of includes

	// camera.cpp, movable.cpp...
	// #include "definitions_include.h"
	// 1 include in each cpp file, gives access to other classes and their methods.


*/


template<class T>
struct point2d;

using width_height = point2d<int>;

using sprite_pointer = Sprite*;

class game_window;

class game_text;

class drawable;

class translational;

class states;

class camera;

class game_view;

class character;

class platform;

class projectile;

class rocket;

class enemy;

class game_environment;


class game_object;

class frame_rate;

enum character_action {
	DEFAULT,
	LOOK_LEFT,
	LOOK_LEFT_AND_SIT,
	SHOOT,
	SHOOT_AND_SIT,
	LOOK_RIGHT,
	LOOK_RIGHT_AND_SIT,
	IN_ROCKET,
};
enum platform_skins {
	USUAl,
	FAKE1,
	FAKE2,
	FAKE3,
	FAKE4,
};
enum enemy_kinds{
	KIND1,
	KIND2,
	KIND3,
	KIND4,
	KIND5,
	ENEMY_COUNT
};

enum symbol_indexes {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	zero,
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	dot,
	koma,
	semicolon,
	colon,
	question_mark,
	exclamation_mark,
	double_quote,
	quote,
	plus,
	minus,
	equal,
	star,
	percent,
	underscore,
	left_bracket,
	right_bracket,
};

string get_current_dir();
string in_cur_dir(const string& relative_path);

vector<string> load_paths_from_txt(const string& path_to_txt);

template <class T>
T generate_random(T min, T max) {
	T subtraction_ = max - min;
	if (subtraction_ == T(0))
		return T(max);
	else if (subtraction_ == max)
		return rand() % ++subtraction_;
	return (rand() % subtraction_ + min);
}


template<class T>
T find_maximum(const T& a, const T& b, const T& c) {
	if (a > c) {
		if (a >= b)
			return a;
		return b;
	}
	else if (b > c)
		return b;
	return c;
}
template<class T>
T find_maximum(vector<T> vec) {
	T max = numeric_limits<T>::min();
	for (const T& el : vec)
		if (max < el)
			max = el;
	return  max;
}

template<class T>
T find_minimum(const T& a, const T& b, const T& c) {
	if (b < a) {
		if (b <= c)
			return b;
		return c;
	}
	else if (c < a)
		return c;
	return a;
}
template<class T>
T find_minimum(vector<T> vec) {
	T min = numeric_limits<T>::max();
	for (const T& el : vec)
		if (min > el)
			min = el;
	return min;
}
template<class T>
T find_average(const T& a, const T& b, const T& c) {
	return (a + b + c) / T(3);
}
template<class T>
T find_average(vector<T> vec) {
	T sum = T(0);
	for (const T& el : vec)
		sum += el;
	return T(sum / double(vec.size()));
}


template <class T>
T precision(const T& value, const int& size) {
	T decades = T(pow(10, size));
	return T(round(value * decades)) / decades;
}
template<class T>
T aspect_ratio(const T& height, const T& width) {
	return height / width;
}