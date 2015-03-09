#include "circle.h"
#include "shape.h"

Circle::Circle(sf::Vector2f position, float radius)
{
	m_vPosition = position;
	m_fRadius = radius;
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle(m_fRadius,50);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(m_vPosition.x-m_fRadius,m_vPosition.y-m_fRadius);
	target.draw(circle);
}

float Circle::getRadius()
{
	return m_fRadius;
}