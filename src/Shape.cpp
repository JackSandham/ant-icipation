#include "shape.h"

Shape::Shape()
{

}

void Shape::setPosition(sf::Vector2f pos)
{
	m_vPosition = pos;
}

void Shape::setColor(sf::Color passedColor)
{
	m_Color = passedColor;
}

sf::Vector2f Shape::getPosition()
{
	return m_vPosition;
}

sf::Color Shape::getColor()
{
	return m_Color;
}