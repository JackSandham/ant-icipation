#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
	public:
		Circle(Vector2D position, float radius);

		float getRadius();
		void move(Vector2D position);

	protected:

	private:
		float m_fRadius;
};

#endif