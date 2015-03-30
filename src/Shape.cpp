#include "shape.h"

Shape::Shape()
{

}

void Shape::setPosition(Vector2D pos)
{
	m_vPosition = pos;
}

void Shape::setColor(sf::Color passedColor)
{
	m_Color = passedColor;
}

Vector2D Shape::getPosition()
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

float Shape::getXPosition(){
	return m_vPosition.getX();
}

float Shape::getYPosition(){
	return m_vPosition.getY();
}