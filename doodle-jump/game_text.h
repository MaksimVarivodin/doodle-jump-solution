#pragma once
#include "declarations.h"
#include "states.h"
class game_text: public states
{	
	map<char, symbol_indexes> translation_table_;
public:
	point2d<float> draw_text(const string & text, const point2d<float> & position) const;
	game_text(const map<char, symbol_indexes>& table, const states & sprites)
		:states::states(sprites), translation_table_(table)
	{
	}
	game_text():translation_table_()
	{
	}
	static game_text create_game_text();
};

