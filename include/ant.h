/**
Document me :)

@author Ryan Wilson 23/02/15 ant-icipation
*/

#ifndef ANT_H
#define ANT_H

#include "randomiser.h"
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
		Ant(Vector2D passedPosition, int width, int height);
		Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor);
		
		void move();
		void moveup();
		void movedown();
		void moveleft();
		void moveright();
		void randomDirection();
		void Update();
		void WallCollision();
		void setMovable(bool bPassedMove);
		void setDirection(Vector2D passedVector);
		void setRadiusVisibility(bool passedVisible);
		bool isMoveable();
		bool radiusIsVisible();
		Vector2D getDirection();
		Circle* getAntRadius();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:

	private:
		Randomiser m_randomiser;
		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;
		bool m_bCanMove;
		bool m_bRadiusVisible;
		Circle* antRadius; //previously in main
		Vector2D m_vDirection;
};
#endif



