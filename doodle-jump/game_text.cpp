#include "definitions_include.h"

point2d<float> game_text::draw_text(const string& text, const point2d<float>& position) const
{
	point2d<float> temp_position = position;
	for (char lett : text) {
		if (lett == ' ')
			temp_position.x_ += 25.f;
		else {
			int index = translation_table_.at(lett);
			this->draw_state(temp_position, index);
			temp_position.x_ += this->get_drawable(index).get_width();
		}
	}
	return temp_position;
}

game_text game_text::create_game_text()
{
	states sprites = states::create_states("\\sprites_data\\letters.txt");
	
	sprites.scale(1.f, 1.f);
	vector<char> letters = {
	'A',	'B',	'C',	'D',	'E', 	'F',	'G',	'H',	'I',	'J',	'K',	'L',	'M',	'N',	'O',	'P',	'Q',	'R',	'S','T',	'U',	'V',	'W',	'X',
	'Y',	'Z',	'a',	'b',	'c',	'd',	'e', 	'f',	'g',	'h',	'i',	'j',	'k',	'l',	'm',	'n',	'o',	'p',	'q',	'r',	's','t',	'u',	'v',
	'w',	'x',	'y',	'z',	'0',	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',	'9',	'.', 	',',	';',	':',	'?',	'!',	'\"',	'\'',	'+',
	'-',	'=',	'*',	'%',	'_',	'(',	')'
	};
	map<char, symbol_indexes> table;
	for (int i = 0; i < letters.size(); i++)
	{
		table[letters[i]] = (symbol_indexes)i;
	}
	return game_text(table, sprites);
}
