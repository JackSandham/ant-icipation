#include "shape.h"

Shape::Shape()
{

}

void Shape::setPosition(Vector2D pos)
{
	m_vPosition = pos;
}

Vector2D Shape::getPosition()
{
	return m_vPosition;
}

float Shape::getXPosition()
{
	return m_vPosition.getX();
}

float Shape::getYPosition()
{
	return m_vPosition.getY();
}