#ifndef FOOD_H
#define FOOD_H

#include "randomiser.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "AABB.h"
#include "Circle.h"

using namespace std;

class Food : public AABB
{
	public:
		Food();

		Food(Vector2D passedPosition, int width, int height, sf::Color passedColor);

		Circle* getFoodRadius();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//This function is used to move the rectangle and ant radius.
		void moveVisualObjects(float xPos, float yPos);
		bool radiusIsVisible();
		bool getCollidable();
		void setCollidable(bool bPassedCollidable);
		void setRadiusVisibility(bool bPassedVisibility);
		void setCollected(bool bPassedCollected);
		bool getCollected();
		void setHome(bool bPassedHome);
		bool getHome();
		void Update();

	protected:

	private:

		float m_fBottom;
		float m_fLeft; 
		float m_fRight; 
		float m_fTop;

		bool m_bIsCollected;
		bool m_bRadiusVisible;
		bool m_bCollidable;
		bool m_bIsHome;
		Circle* foodRadius; //previously in main
};
#endif


