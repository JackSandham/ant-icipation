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
void Shape::draw(sf::RenderTarget& target /** Context for rendering */, 
sf::RenderStates states /** Primitive shpaes to render */) const
{

}