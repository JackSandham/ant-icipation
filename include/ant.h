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
		Ant(Vector2D passedPosition, int width, int height);
		Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor);
		
		void move();
		void moveup();
		void movedown();
		void moveleft();
		void moveright();
		void randomMovement();
		void Update();
		void WallCollision(Ant ant);
		void setMovable(bool bPassedMove);
		bool isMoveable();
		Circle* getAntRadius();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:

	private:
		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;
		bool m_bCanMove;
		Circle* antRadius; //previously in main
		Vector2D m_vDirection;
};
#endif



