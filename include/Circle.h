#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class Circle : public Shape
{
	public:
		Circle(Vector2D position, float radius);
		Circle(Vector2D position, float radius, sf::Color passedColor);

		float getRadius();
		void move(Vector2D position);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::CircleShape circle;
	private:
		float m_fRadius;
};

#endif