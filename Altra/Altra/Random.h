//
// Created by Mörkönenä on 17.2.2019
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <limits.h>

template<typename Real = float>
class Random
{
private:
	std::mt19937_64 engine;
	std::uniform_real_distribution<Real> random;

public:
	Random(uint64_t seed) : engine(seed), random() {}

	Real Next()
	{
		return random(engine);
	}

	Real Next(Real min, Real max)
	{
		return min + random(engine) * (max - min);
	}


	Real operator()()
	{
		return Next();
	}

	Real operator()(Real min, Real max)
	{
		return Next(min, max);
	}


	template<typename Integer>
	Integer Next(Integer min, Integer max)
	{
		return min + Integer((*this)() * (max - min));
	}


	void Reset()
	{
		random.reset();
	}

	void Seed(int seed)
	{
		engine.seed(seed);
	}
};

#endif // !RANDOM_H