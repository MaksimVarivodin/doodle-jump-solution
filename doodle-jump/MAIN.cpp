// doodle-jump.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "definitions_include.h"


int main(int argc, char* argv[])
{
	int window_height = 1024;
	int window_width = 640;
	if (argc > 1) {
		// |game name| argument name | argument value |
		if (argc == 3)
		{
			// copy 3-rd element to string
			string window_size(argv[2]);
			// find divider
			size_t find_x = window_size.find("x");
			// copy substring of width
			string str_window_width = window_size.substr(0, find_x);
			// delete substring of width
			window_size.erase(0, find_x + 1);
			// parse width
			window_width = stoi(str_window_width);

			// parse height
			window_height = stoi(window_size);


		}
	}
#ifdef _CONSOLE_DEBUG
	cout << "window_width " << window_width << endl;
#endif // _CONSOLE_DEBUG

#ifdef _CONSOLE_DEBUG
	cout << "window_height " << window_height << endl;
#endif // _CONSOLE_DEBUG


	srand(time(NULL));
	game_window* game_win = new game_window(window_width, window_height);

	int res = run(game_win);
	delete game_win;

	return 0;
}
