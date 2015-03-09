#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class Circle : public Shape
{
	public:
		Circle(sf::Vector2f position, float radius);

		float getRadius();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		float m_fRadius;
};

#endif