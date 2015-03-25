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
#include "Circle.h"
using namespace std;

class Ant : public AABB
{
	public:
		Ant();
		Ant(sf::Vector2f passedPosition, int width, int height) : AABB(passedPosition,  width,  height){}
		Ant(sf::Vector2f passedPosition, int width, int height, sf::Color passedColor) ;
		
		void move();
		void moveup();
		void movedown();
		void moveleft();
		void moveright();
		void randomMovement();
		void Update();
		void WallCollision(Ant ant);
		Circle* getAntRadius();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:

	private:
		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;
		Circle* antRadius; //previously in main
		sf::Vector2f m_vDirection;
};
#endif



