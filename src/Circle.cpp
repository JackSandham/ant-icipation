#include "circle.h"
#include "shape.h"

Circle::Circle(Vector2D position, float radius)
{
	m_vPosition = position;
	m_fRadius = radius;
}

void Circle::move(Vector2D position)
{
	m_vPosition = position;
}

float Circle::getRadius()
{
	return m_fRadius;
}