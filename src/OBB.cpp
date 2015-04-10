#include "OBB.h"
#include "shape.h"

OBB::OBB(Vector2D position, float width, float height,float angle)
{
	m_vPosition = position;
	m_fWidth = width;
	m_fHeight = height;
	m_fAngle = angle;
	m_vOrigin = (Vector2D(m_fWidth/2,m_fHeight/2));
}

float OBB::getHalfWidth()
{
	return m_fWidth/2;
}

float OBB::getHalfHeight()
{
	return m_fHeight/2;
}

float OBB::getAngle()
{
	return m_fAngle;
}