#include "Food.h"
#include <Windows.h>

Food::Food()
{

}

Food::Food(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	foodRadius = new Circle(getPosition(), 50);// foods detection radius
	m_bCollidable = true;
	m_bIsCollected = false;

	float fWidth = (float)width;
	float fHeight = (float)height;

	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("food"));
	m_sprite.setScale(fWidth / tm->getTexture("food")->getSize().x, fHeight / tm->getTexture("food")->getSize().y);
	m_sprite.setPosition(passedPosition.getX() + 300, passedPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);
}

void Food::setPosition(Vector2D pos)
{
	m_vPosition = pos;
	m_sprite.setPosition(pos.getX() + 300, pos.getY() + 100);
	rectangle.setPosition(pos.getX(), pos.getY());
}

Circle* Food::getFoodRadius()
{
	return foodRadius;
}

bool Food::isCollidable()
{
	return m_bCollidable;
}
	
void Food::setCollidable(bool bPassedCollidable)
{
	m_bCollidable = bPassedCollidable;
}

float Food::distanceTo(Vector2D vPos)
{
	float dX = vPos.getX() - getPosition().getX();
	float dY = vPos.getY() - getPosition().getY();
	return std::sqrt((dX * dX) + (dY * dY));
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}