/**
Document me :)

@author Ryan Wilson 23/02/15 ant-icipation
*/

#ifndef ANT_H
#define ANT_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "AABB.h"
#include "Circle.h"
#include "randomiser.h"
#include "TextureManager.h"
#include "antEater.h"
#include <CollisionsManager.h>

using namespace std;

class Ant : public AABB, public sf::Drawable
{
	public:
		Ant();
		Ant(Vector2D passedPosition, int width, int height);
		
		void Update(AntEater &passedAntEater, CollisionsManager &passedColMan);
		void setMovable(bool bPassedMove);
		void setDirection(Vector2D passedVector);
		void setRadiusVisibility(bool passedVisible);
		void setFood(bool bPassedFood);
		void setColliding(bool bColliding);
		void setFleeing(bool bFleeing);
		void setFacingEater(bool bFacingEater);
		bool isMoveable();
		bool isColliding();
		bool isFacingEater();
		bool isFleeing();
		bool radiusIsVisible();
		bool getFood();
		Vector2D getDirection();
		Vector2D getStartPos();
		Circle* getAntRadius();
		
		bool antEaterEats(AntEater &passedAntEater, CollisionsManager &passedColMan);
		void facingEater(AntEater &passedAntEater, CollisionsManager &passedColMan);

		//This function is used to move the rectangle and ant radius.
		void moveVisualObjects(float xPos, float yPos);
		int getNumber();
		void setNumber(int iPassedNumber);
		
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		bool m_bCanMove;
		bool m_bHasFood;
		bool m_bRadiusVisible;
		bool m_bAntColliding;
		bool m_bFleeing;
		bool m_bFacingEater;
		int m_iNumber;
		Circle* antRadius; //previously in main
		Vector2D m_vDirection;
		Vector2D m_vStartPos;

		sf::Sprite m_sprite;
};
#endif



