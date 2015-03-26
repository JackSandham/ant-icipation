#include "circle.h"
#include "shape.h"

Circle::Circle(Vector2D position, float radius)
{
	m_vPosition = position;
	m_fRadius = radius;
}
Circle::Circle(Vector2D position, float radius, sf::Color passedColor)
{
	m_vPosition = position;
	m_fRadius = radius;
	setColor(passedColor);
	circle.setRadius(m_fRadius);
	circle.setPosition(m_vPosition.getX()-m_fRadius,m_vPosition.getY()-m_fRadius);
	circle.setFillColor(passedColor);
}

void Circle::move(Vector2D position)
{
	m_vPosition = position;
	circle.setPosition(m_vPosition.getX()-m_fRadius,m_vPosition.getY()-m_fRadius);
}
void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(circle);
}

float Circle::getRadius()
{
	return m_fRadius;
}