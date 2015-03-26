#ifndef AABB_H
#define AABB_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class AABB : public Shape
{
	public:
		AABB();
		AABB(Vector2D position, float width, float height);
		AABB(Vector2D position, float width, float height, sf::Color passedColor);
	
		void setMin();
		void setMax();
		void setPosition(Vector2D passedVector);
		float getHalfWidth();
		float getHalfHeight();
		Vector2D getMin();
		Vector2D getMax();
		sf::RectangleShape* getRectangle();
	
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::RectangleShape rectangle;

	private:
		float m_fWidth;
		float m_fHeight;
		Vector2D m_vMax;
		Vector2D m_vMin;
};

#endif