//
// Created by Mörkönenä on 25.8.2018
//

#ifndef RANGE_H
#define RANGE_H

template<typename Number>
class Range
{
private:
	Number min;
	Number max;

public:
	Range();
	Range(Number min, Number max);

	bool Inside(Number number) const;

	Number GetMin() const;
	Number GetMax() const;
	Number GetValue(float x) const;
	Number GetLength() const;
};

template<typename Number>
inline Range<Number>::Range()
{
	min = 0;
	max = 0;
}

template<typename Number>
inline Range<Number>::Range(Number min, Number max)
{
	this->min = min;
	this->max = max;
}

template<typename Number>
inline bool Range<Number>::Inside(Number number) const
{
	return (number >= min) && (number <= max);
}

template<typename Number>
inline Number Range<Number>::GetMin() const
{
	return min;
}

template<typename Number>
inline Number Range<Number>::GetMax() const
{
	return max;
}

template<typename Number>
inline Number Range<Number>::GetValue(float x) const
{
	return min + Number(x * (max - min));
}

template<typename Number>
inline Number Range<Number>::GetLength() const
{
	return (max - min);
}

#endif // !RANGE_H