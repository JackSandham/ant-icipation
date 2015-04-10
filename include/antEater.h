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
#include "TextureManager.h"

using namespace std;

class AntEater : public AABB, public sf::Drawable
{
	public:
		AntEater();
		AntEater(Vector2D passedPosition, int width, int height);

		void Update();
	
		void setMovable(bool bPassedMove);
		void setDirection(Vector2D passedVector);
		void setRadiusVisibility(bool passedVisible);
		void setFood(bool bPassedFood);
		void setColliding(bool bColliding);
		bool isMoveable();
		bool isColliding();
		bool radiusIsVisible();
		bool getFood();
		Vector2D getDirection();
		Circle* getAntEaterOuterRadius();
		Circle* getAntEaterInnerRadius();
		//This function is used to move the rectangle and ant radius.
		void moveVisualObjects(float xPos, float yPos);		
		
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;
		bool m_bCanMove;
		bool m_bHasFood;
		bool m_bRadiusVisible;
		bool m_bAntColliding;
		Circle* anteaterInnerRadius; 
		Circle* anteaterOuterRadius;
		Vector2D m_vDirection;
		sf::Sprite m_sprite; 
};


#endif
