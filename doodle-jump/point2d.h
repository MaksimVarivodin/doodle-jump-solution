#pragma once

#include "declarations.h"


/// <summary>
/// 
/// A structure that holds x- and y- coordinate.
/// Provides basic operator overloading to work with points.
/// 
/// </summary>
/// <typeparam name="float"> </typeparam>
/// <typeparam name="int"> </typeparam>
template<class T = float>
struct point2d {

	T x_;
	T y_;

	point2d<T>& operator= (const point2d<T>& other);

	point2d<T> operator+ (const point2d<T>& other)const;

	point2d<T> operator- (const point2d<T>& other)const;

	point2d<T> operator* (const T& value)const;

	point2d<T> operator/ (const T& value)const;

	point2d<T>& operator+=(const point2d<T>& other);

	point2d<T>& operator-=(const point2d<T>& other);

	point2d<T>& operator*= (const T& value);

	point2d<T>& operator/= (const T& value);

	point2d<T>& to_vector(const point2d<T>& vector_end);

	T vector_length() const;

	point2d<T>& normalize();
	template<class U, class W>
	point2d(const U& x, const W& y)
		: x_(T(x)), y_(T(y))
	{
	}
	template<class U>
	point2d(const U& x)
		: point2d(static_cast<T>(x), T(0))
	{
	}
	point2d()
		: point2d(T(0))
	{
	}
};

template<class T>
inline point2d<T>& point2d<T>::operator=(const point2d<T>& other)
{
	x_ = other.x_;
	y_ = other.y_;
	return *this;
}
template<class T>
inline point2d<T> point2d<T>::operator+(const point2d<T>& other)const
{
	return point2d<T>{
		x_ + other.x_,
			y_ + other.y_
	};
}

template<class T>
inline point2d<T> point2d<T>::operator-(const point2d<T>& other) const
{
	return point2d<T>{
		x_ - other.x_,
		y_ - other.y_
	};
}

template<class T>
inline point2d<T> point2d<T>::operator*(const T& value) const
{
	return point2d<T>{
		x_*value,
			y_*value
	};
}

template<class T>
inline point2d<T> point2d<T>::operator/(const T& value) const
{
	// i don't want to throw any exceptions, 
	// I'll just pass max value of the type
	// (infinity or max int value - depends on the template type)
	if (value == T(0))
		return point2d<T>{
				numeric_limits<T>::max(),
				numeric_limits<T>::max()
		};
	return point2d<T>{
		x_ / value,
			y_ / value
	};
}

template<class T>
inline point2d<T>& point2d<T>::operator+=(const point2d<T>& other)
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

template<class T>
inline point2d<T>& point2d<T>::operator-=(const point2d<T>& other)
{
	x_ -= other.x_;
	y_ -= other.y_;
	return *this;
}

template<class T>
inline point2d<T>& point2d<T>::operator*=(const T& value)
{
	x_ *= value;
	y_ *= value;
	return *this;
}

template<class T>
inline point2d<T>& point2d<T>::operator/=(const T& value)
{
	// same as in operator/
	if (value != T(0)){
		x_ /= value;
		y_ /= value;
	}else {
		x_ = numeric_limits<T>::max();
		y_ = numeric_limits<T>::max();
	}	
	return *this;
}

template<class T>
inline point2d<T>& point2d<T>::to_vector(const point2d<T>& vector_end)
{
	x_ = vector_end.x_ - x_;
	y_ = vector_end.y_ - y_;
	return *this;
}

template<class T>
inline T point2d<T>::vector_length() const
{	
	return (T)sqrt(x_* x_ + y_ * y_);
}

template<class T>
inline point2d<T>& point2d<T>::normalize()
{
	// TODO: insert return statement here
	operator/=(vector_length());
	return *this;
}



