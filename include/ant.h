#ifndef ANT_H
#define ANT_H


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "AABB.h"

using namespace std;


class Ant : public AABB
{
private:
	float m_fBottom, m_fLeft, m_fRight, m_fTop;
public:
	
	Ant();
	Ant(sf::Vector2f passedPosition, int width, int height) : AABB(passedPosition,  width,  height){}
	Ant(sf::Vector2f passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor){}
	void Update();
	bool Collision(Ant ant);
	
//Ryan Wilson 23/02/15 ant-icipation







};
#endif



