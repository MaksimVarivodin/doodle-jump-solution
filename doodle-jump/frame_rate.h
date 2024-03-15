#pragma once
#include "declarations.h"
class frame_rate
{
	int array_size_;
	int frame_counter_ = 0;
	int average_frame_rate_ = 0;
	int minimum_frame_rate_ = 0;
	int maximum_frame_rate_ = 0;

	vector<int> f_rate_values_;
	int cur_index_ = 0;

	mutable mutex mtx_;
	thread* frame_rate_thread_;

	void frame_rate_thread_method();
	void set_array_index();
	void calculate_frames();
	bool is_thread_stopped()const { return frame_rate_thread_ == nullptr; }
public:
	frame_rate()
		: 
		array_size_(24),
		f_rate_values_(vector<int>(array_size_, 0)),
		frame_rate_thread_(nullptr)
	{

	}
	frame_rate(const frame_rate& other)
		: 
		array_size_(24),
		f_rate_values_(vector<int>(array_size_, 0)),
		frame_rate_thread_(nullptr) {
		frame_counter_ = other.frame_counter_;
	}
	~frame_rate()
	{
		if (!is_thread_stopped()) {
			delete frame_rate_thread_;

#ifdef _CONSOLE_DEBUG
			cout << "frame_rate_thread destroyed" << endl;
#endif // _CONSOLE_DEBUG

		}


	}

	frame_rate& operator++();
	frame_rate operator++(int);
	void launch();
	void stop();

	int get_average_frame_rate() const;
	int get_minimum_frame_rate() const;
	int get_maximum_frame_rate() const;
	float get_elapsed_time() const;
	string to_string() const;

};
