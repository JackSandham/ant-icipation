#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H

#include "OBB.h"
#include "AABB.h"
#include "Circle.h"
#include "Vector2D.h"
#include "Shape.h"

class CollisionsManager
{
	public:
		CollisionsManager();

		bool AABBtoCircleCollision(AABB &aabb,Circle &circle);
		bool AABBtoAABBCollision(AABB &aabb,AABB &aabb2);
		bool OBBtoCircleCollision(OBB &obb, Circle &circle);
		bool CircletoCircleCollision(Circle &circle, Circle &circle2);

		void correctPosition(Shape &passedShape);
	protected:

	private:
		float m_fFinalDistance;
		Vector2D m_Normal;
};

#endif