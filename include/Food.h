#ifndef FOOD_H
#define FOOD_H

#include "randomiser.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "TextureManager.h"
#include "AABB.h"
#include "Circle.h"

using namespace std;

class Food : public AABB, public sf::Drawable
{
	public:
		Food();
		Food(Vector2D passedPosition, int width, int height);

		Circle* getFoodRadius();

		bool isCollidable();
		void setCollidable(bool bPassedCollidable);
		void setPosition(Vector2D passedVector);
		float distanceTo(Vector2D vPos);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		bool m_bIsCollected;
		bool m_bCollidable;
		Circle* foodRadius; //previously in main

		sf::Sprite m_sprite;
};
#endif


