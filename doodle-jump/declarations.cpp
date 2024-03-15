
#include "definitions_include.h"

string get_current_dir() {
	string result;
	char* output = new char[500];
	WCHAR path[500];
	GetModuleFileName(NULL, path, 500);
	sprintf(output, "%ws", path);
	result = output;
	result = result.substr(0, result.find_last_of("\\/"));
	delete[] output;
	return result;
}

string in_cur_dir(const string& relative_path)
{
	return get_current_dir() + relative_path;
}

vector<string> load_paths_from_txt(const string& path_to_txt)
{
	ifstream ifout;
	vector<string> result;

	result.reserve(200);
	string current_dir = get_current_dir();
	ifout.open(current_dir + path_to_txt);

	if (ifout.is_open()){
		while(!ifout.eof()){
			string path;
			getline(ifout, path);
			result.push_back(current_dir + path);
		}	
	}
	return result;
}
