#include "definitions_include.h"

void frame_rate::frame_rate_thread_method()
{
	while (true) {
		// чтобы сделать 50 замера в секунду 
		// необходимо заснуть на 0,02-ую секунды 
		// или на 20 миллисекунд
		// или на 20000 микросекунды
		// выбрал последнее
		
		this_thread::sleep_for(chrono::microseconds(1000000 / array_size_));
		
		lock_guard<mutex> lock(mtx_);

		f_rate_values_[cur_index_] = frame_counter_ * array_size_;

		calculate_frames();

		set_array_index();

		frame_counter_ = 0;

	}
}

void frame_rate::set_array_index()
{
	if (cur_index_ == array_size_ - 1)
		this->cur_index_ = 0;
	else
		this->cur_index_++;
}

void frame_rate::calculate_frames()
{
	if (cur_index_ == array_size_ -1 || cur_index_ == (array_size_ -1 )/2) {
		average_frame_rate_ = find_average(f_rate_values_);
		minimum_frame_rate_ = find_minimum(f_rate_values_);
		maximum_frame_rate_ = find_maximum(f_rate_values_);

#ifdef _CONSOLE_DEBUG
		cout << average_frame_rate_<< endl;
#endif // _CONSOLE_DEBUG

	}
}

frame_rate& frame_rate::operator++()
{
	mtx_.lock();
	frame_counter_++;
	frame_rate& link = *this;
	mtx_.unlock();
	return link;
}

frame_rate frame_rate::operator++(int)
{
	this->operator++();
	mtx_.lock();	
	frame_rate temp = *this;
	mtx_.unlock();
	
	return temp;
}

void frame_rate::launch()
{
	if (!is_thread_stopped())
		stop();
	this->frame_rate_thread_ = new thread{ &frame_rate::frame_rate_thread_method, this };
	this->frame_rate_thread_->detach();


#ifdef _CONSOLE_DEBUG
	cout << "frame_rate_thread launched" << endl;
#endif // _CONSOLE_DEBUG
}

void frame_rate::stop()
{
	if (!is_thread_stopped()){
		this->f_rate_values_ = vector<int>(this->array_size_, 0);
		delete frame_rate_thread_;
		frame_rate_thread_ = nullptr;
	}	

#ifdef _CONSOLE_DEBUG
	cout << "frame_rate_thread stopped" << endl;
#endif // _CONSOLE_DEBUG

}

int frame_rate::get_average_frame_rate() const 
{
	mtx_.lock();
	const int value = average_frame_rate_;
	mtx_.unlock();
	return value;
}

int frame_rate::get_minimum_frame_rate() const
{
	mtx_.lock();
	const int value = minimum_frame_rate_;
	mtx_.unlock();
	return value;
}

int frame_rate::get_maximum_frame_rate() const
{
	mtx_.lock();
	const int value = maximum_frame_rate_;
	mtx_.unlock();
	return value;
}

float frame_rate::get_elapsed_time() const
{
#ifdef _CONSOLE_DEBUG
	float time = 1.f / (float)array_size_;
	return time;
#endif // _CONSOLE_DEBUG
#ifndef _CONSOLE_DEBUG
	int avg = get_average_frame_rate();
	int min = get_minimum_frame_rate();
	if (avg > 0)
		return 1.f / (float)avg;
	else if (min > 0 )
		return 1.f / (float)min;
	else
	return  1.f/ (float)array_size_;
#endif // _CONSOLE_DEBUG
	
}

string frame_rate::to_string() const
{
	return
		"Avg: " + std::to_string(get_average_frame_rate()) + "\n" +
		"Max: " + std::to_string(get_maximum_frame_rate()) + "\n" +
		"Min: " + std::to_string(get_minimum_frame_rate());
}

