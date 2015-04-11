#ifndef AABB_H
#define AABB_H

#include <SFML\Graphics.hpp>

#include "Shape.h"

class AABB : public Shape
{
	public:
		AABB();
		AABB(Vector2D position, float width, float height);
	
		void setMin();
		void setMax();
		void setPosition(Vector2D passedVector);
		float getHalfWidth();
		float getHalfHeight();
		Vector2D getMin();
		Vector2D getMax();
	
	protected:
		sf::RectangleShape rectangle;
		Vector2D m_vMax;
		Vector2D m_vMin;

	private:
		float m_fWidth;
		float m_fHeight;
		
};

#endif