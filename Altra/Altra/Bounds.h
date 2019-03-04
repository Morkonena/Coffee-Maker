//
// Created by Mörkönenä on 24.2.2019
//

#ifndef BOUNDS_H
#define BOUNDS_H

template<typename Number>
class Bounds
{
private:
	Number Left, Top, Right, Bottom;

public:
	Bounds() = default;
	Bounds(Number left, Number top, Number right, Number bottom);

	template<typename T>
	bool Inside (T x, T y) const;

	Number GetLeft() const;
	Number GetTop() const;
	Number GetRight() const;
	Number GetBottom() const;
};

template<typename Number>
inline Bounds<Number>::Bounds(Number left, Number top, Number right, Number bottom) :
	Left(left), Top(top), Right(right), Bottom(bottom)
{}

template<typename Number>
inline Number Bounds<Number>::GetLeft() const
{
	return Left;
}

template<typename Number>
inline Number Bounds<Number>::GetTop() const
{
	return Top;
}

template<typename Number>
inline Number Bounds<Number>::GetRight() const
{
	return Right;
}

template<typename Number>
inline Number Bounds<Number>::GetBottom() const
{
	return Bottom;
}

template<typename Number>
template<typename T>
inline bool Bounds<Number>::Inside(T x, T y) const
{
	return Number(x) >= Left && Number(x) <= Right && Number(y) >= Bottom && Number(y) <= Top;
}

#endif // !BOUNDS_H

