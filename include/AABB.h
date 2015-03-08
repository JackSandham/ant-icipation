#ifndef AABB_H
#define AABB_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class AABB : public Shape
{
	public:
		AABB();
		AABB(sf::Vector2f position, float width, float height);
		AABB(sf::Vector2f position, float width, float height, sf::Color passedColor);
	
		void setMin();
		void setMax();
		void setPosition(sf::Vector2f passedVector);
		float getHalfWidth();
		float getHalfHeight();
		sf::Vector2f getMin();
		sf::Vector2f getMax();
		sf::RectangleShape* getRectangle();
	
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::RectangleShape rectangle;

	private:
		float m_fWidth;
		float m_fHeight;
		sf::Vector2f m_vMax;
		sf::Vector2f m_vMin;
};

#endif