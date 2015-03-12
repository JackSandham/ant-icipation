#include "Randomiser.h"

/**
Creates a default randomiser object with a lower and upper bound of 0 and 10 respectively. */
Randomiser::Randomiser()
{
	m_randomGenerator.seed(time(0));
	m_bounds = std::uniform_real_distribution<float>(0.f, 10.f);
}

/**
Returns the next random number using the current randomiser bounds. *

@return The next random number. */
float Randomiser::getRandom()
{
	return m_bounds(m_randomGenerator);
}

/**
Sets the lower and upper bounds of the randomiser. Future calls to getRandom() will produce numbers within
the given range. If the upper bound was less than or equal to the minimum bound, no action is taken. This
function also returns the next random number using the new bounds.

@param fLower The lower randomiser bound.
@param fUpper The upper randomiser bound.
@return The next random number. */
float Randomiser::getRandom(float fLower, float fUpper)
{
	if (fUpper <= fLower)
	{
		return -1;
	}
	m_bounds = std::uniform_real_distribution<float>(fLower, fUpper);

	return m_bounds(m_randomGenerator);
}

/**
Sets the lower and upper bounds of the randomiser. Future calls to getRandom() will produce numbers within
the given range. If the upper bound was less than or equal to the minimum bound, no action is taken.

@param fLower The lower bound
@param fUpper The upper bound. */
void Randomiser::setRandomiserBounds(float fLower, float fUpper)
{
	if (fLower < fUpper)
	{
		m_bounds = std::uniform_real_distribution<float>(fLower, fUpper);
	}	
}
