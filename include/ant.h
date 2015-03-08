/**
Document me :)

@author Ryan Wilson 23/02/15 ant-icipation
*/

#ifndef ANT_H
#define ANT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "AABB.h"

using namespace std;

class Ant : public AABB
{
	public:
		Ant();
		Ant(sf::Vector2f passedPosition, int width, int height) : AABB(passedPosition,  width,  height){}
		Ant(sf::Vector2f passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor){}
		
		void Update();
		bool Collision(Ant ant);

	protected:

	private:
		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;
};
#endif