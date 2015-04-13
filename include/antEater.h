/**
antEater class

watch this space
@author Ryan Wilson 2/4/2015
*/

#ifndef ANTEATER_H
#define ANTEATER_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "AABB.h"
#include "Circle.h"
#include "randomiser.h"
#include "TextureManager.h"
#include "Alarm.h"
#include "AlarmList.h"

using namespace std;

class AntEater : public AABB, public sf::Drawable, public AlarmListener
{
	public:
		AntEater();
		AntEater(Vector2D passedPosition, int width, int height);

		void update();
	
		void setMovable(bool bPassedMove);
		void setDirection(Vector2D passedVector);
		void setRadiusVisibility(bool passedVisible);
		void setFood(float bPassedFood);
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

		void wander();
		float getDetectionRadius() const;	
		float distanceTo(Vector2D vPos);
		void moveTowards(Vector2D vPos);
		void changeTargetPosition();
		void antEaten();
		bool isHungry();

		void alarmExpired(AlarmEvent* e);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		int m_iHungerLevel;
		bool m_bCanMove;
		bool m_bHasFood;
		bool m_bRadiusVisible;
		bool m_bAntColliding;
		float m_fDetectionRadius;
		Circle* anteaterInnerRadius; 
		Circle* anteaterOuterRadius;
		Vector2D m_vDirection;
		Vector2D m_vTargetPosition;
		Randomiser m_randomiser;
		sf::Sprite m_sprite;
		sf::Sprite m_spriteVisionRadius;
};


#endif
