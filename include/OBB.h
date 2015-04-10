#ifndef OBB_H
#define OBB_H

#include "Shape.h"

class OBB : public Shape
{
	public:
		OBB(Vector2D position, float width, float height, float angle);
		
		float getHalfWidth();
		float getHalfHeight();
		float getAngle();

	protected:

	private:
		float m_fWidth;
		float m_fHeight;
		float m_fAngle;
};

#endif