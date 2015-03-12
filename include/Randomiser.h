/**
A random number generator.

Generated numbers are float values. The randomiser can be configured to produce numbers between a 
configurable lower and upper bound. A default randomiser will produce numbers between 0 and 9.9999999.

Note that the lower bound is inclusive and the upper bound is exclusive.

@author Nathan
*/


#ifndef RANDOMISER_H
#define RANDOMISER_H

#include <random>
#include <time.h>

class Randomiser
{
	public:
		Randomiser();

		float getRandom();
		float getRandom(float fMin, float fMax);
		void setRandomiserBounds(float fMin, float fMax);

	protected:

	private:
		std::mt19937 m_randomGenerator;
		std::uniform_real_distribution<float> m_bounds;
};

#endif