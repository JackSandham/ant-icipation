/**
antEater class

watch this space
@author Ryan Wilson 2/4/2015
*/

#ifndef ANTEATER_H
#define ANTEATER_H

#include "randomiser.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "AABB.h"
#include "Circle.h"

using namespace std;

class Eater : public AABB
{
public:
	Eater();
	Eater(Vector2D passedPosition, int width, int height, sf::Color passedColor);

	void Update();
};


#endif