#ifndef SHAPE_H
#define SHAPE_H

#include "Vector2D.h"

class Shape
{
	public:
		Shape();

		void setPosition(Vector2D pos);
		Vector2D& getPosition();
		float getXPosition();
		float getYPosition();

	protected:
		Vector2D m_vPosition;
		Vector2D m_vOrigin;

	private:

};

#endif