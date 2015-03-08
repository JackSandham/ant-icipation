#include "AABB.h"
#include "shape.h"


AABB::AABB()
{

}
AABB::AABB(sf::Vector2f position, float width, float height)
{
	m_vPosition = position;
	m_fWidth = width;
	m_fHeight = height;
	m_vOrigin = (sf::Vector2f(m_fWidth/2,m_fHeight/2));

	m_vMin = sf::Vector2f(position.x-width/2,position.y-height/2);
	m_vMax = sf::Vector2f(position.x+width/2,position.y+height/2);

	Rectangle.setSize(sf::Vector2f(m_fWidth,m_fHeight));
	Rectangle.setOrigin(m_vOrigin);
	Rectangle.setPosition(m_vPosition);
}
AABB::AABB(sf::Vector2f position, float width, float height, sf::Color passedColor)
{
	m_vPosition = position;
	m_fWidth = width;
	m_fHeight = height;
	m_vOrigin = (sf::Vector2f(m_fWidth/2,m_fHeight/2));

	m_vMin = sf::Vector2f(position.x-width/2,position.y-height/2);
	m_vMax = sf::Vector2f(position.x+width/2,position.y+height/2);

	setColor(passedColor);
	Rectangle.setFillColor(passedColor);

	Rectangle.setSize(sf::Vector2f(m_fWidth,m_fHeight));
	Rectangle.setOrigin(m_vOrigin);
	Rectangle.setPosition(m_vPosition);
}
void AABB::setPosition(sf::Vector2f passedVector)
{
	m_vPosition = passedVector;
	Rectangle.setPosition(passedVector);
}
void AABB::setMin()
{
	m_vMin = sf::Vector2f(m_vPosition.x-m_fWidth/2,m_vPosition.y-m_fHeight/2);
	
}
void AABB::setMax()
{
	m_vMax = sf::Vector2f(m_vPosition.x+m_fWidth/2,m_vPosition.y+m_fHeight/2);
}
void AABB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Rectangle);
}

float AABB::getHalfWidth()
{
	return m_fWidth/2;
}
float AABB::getHalfHeight()
{
	return m_fHeight/2;
}


sf::Vector2f AABB::getMin()
{
	return m_vMin;
}

sf::Vector2f AABB::getMax()
{
	return m_vMax;
}
sf::RectangleShape* AABB::getRectangle()
{
	return &Rectangle;
}