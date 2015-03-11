#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class Circle : public Shape
{
	public:
		Circle(sf::Vector2f position, float radius);
		Circle(sf::Vector2f position, float radius, sf::Color passedColor);

		float getRadius();
		void move(sf::Vector2f position);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::CircleShape circle;
	private:
		float m_fRadius;
};

#endif