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
	sf::Vector2f direction;
public:
	
	Ant();
	Ant(sf::Vector2f passedPosition, int width, int height) : AABB(passedPosition,  width,  height){}
	Ant(sf::Vector2f passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor){}

	void move();
	void moveup();
	void movedown();
	void moveleft();
	void moveright();
	void randomMovement();
	void Update();
	void WallCollision(Ant ant);
	
//Ryan Wilson 23/02/15 ant-icipation







};
#endif



