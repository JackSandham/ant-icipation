#include "AABB.h"
#include "shape.h"

AABB::AABB()
{

}

AABB::AABB(Vector2D position, float width, float height)
{
	m_vPosition = position;
	m_fWidth = width;
	m_fHeight = height;
	m_vOrigin = (Vector2D(m_fWidth/2,m_fHeight/2));

	m_vMin = Vector2D(position.getX()-width/2,position.getY()-height/2);
	m_vMax = Vector2D(position.getX()+width/2,position.getY()+height/2);

	rectangle.setSize(sf::Vector2f(m_fWidth,m_fHeight));
	rectangle.setOrigin(m_vOrigin.getX(),m_vOrigin.getY());
	rectangle.setPosition(m_vPosition.getX(),m_vPosition.getY());
}

AABB::AABB(Vector2D position, float width, float height, sf::Color passedColor)
{
	m_vPosition = position;
	m_fWidth = width;
	m_fHeight = height;
	m_vOrigin = (Vector2D(m_fWidth/2,m_fHeight/2));

	m_vMin = Vector2D(position.getX()-width/2,position.getY()-height/2);
	m_vMax = Vector2D(position.getX()+width/2,position.getY()+height/2);

	setColor(passedColor);
	rectangle.setFillColor(passedColor);

	rectangle.setSize(sf::Vector2f(m_fWidth,m_fHeight));
	rectangle.setOrigin(m_vOrigin.getX(),m_vOrigin.getY());
	rectangle.setPosition(m_vPosition.getX(),m_vPosition.getY());
}

void AABB::setPosition(Vector2D passedVector)
{
	m_vPosition = passedVector;
	rectangle.setPosition(passedVector.getX(),passedVector.getY());
}

void AABB::setMin()
{
	m_vMin = Vector2D(m_vPosition.getX()-m_fWidth/2,m_vPosition.getY()-m_fHeight/2);
	
}

void AABB::setMax()
{
	m_vMax = Vector2D(m_vPosition.getX()+m_fWidth/2,m_vPosition.getY()+m_fHeight/2);
}

void AABB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle);
}

float AABB::getHalfWidth()
{
	return m_fWidth/2;
}

float AABB::getHalfHeight()
{
	return m_fHeight/2;
}

Vector2D AABB::getMin()
{
	return m_vMin;
}

Vector2D AABB::getMax()
{
	return m_vMax;
}

sf::RectangleShape* AABB::getRectangle()
{
	return &rectangle;
}