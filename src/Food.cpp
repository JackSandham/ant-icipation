#include "Food.h"
#include <Windows.h>

Food::Food()
{

}

Food::Food(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	foodRadius = new Circle(getPosition(), 50);// foods detection radius
	m_bRadiusVisible = true;
	m_bCollidable =true;
	m_bIsCollected =false;
	m_bIsHome=false;
	Update();

	float fWidth = (float)width;
	float fHeight = (float)height;

	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("food"));
	m_sprite.setScale(fWidth / tm->getTexture("food")->getSize().x, fHeight / tm->getTexture("food")->getSize().y);
	m_sprite.setPosition(passedPosition.getX() + 300, passedPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);
}

void Food::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
}

void Food::setRadiusVisibility(bool bPassedVisibility)
{
	m_bRadiusVisible = bPassedVisibility;
}

bool Food::radiusIsVisible()
{
	return m_bRadiusVisible;
}

Circle* Food::getFoodRadius()
{
	return foodRadius;
}

bool Food::getCollidable()
{
	return m_bCollidable;
}
	
void Food::setCollidable(bool bPassedCollidable)
{
	m_bCollidable = bPassedCollidable;
}

void Food::setCollected(bool bPassedCollected)
{
	m_bIsCollected=bPassedCollected;
}

bool Food::getCollected()
{
	return m_bIsCollected;
}

void Food::setHome(bool bPassedHome)
{
	m_bIsHome=bPassedHome;
}

bool Food::getHome()
{
	return m_bIsHome;
}

int Food::getFoodNumber()
{
	return m_iNumber;
}

void Food::setFoodNumber(int iFoodNumber)
{
	m_iNumber=iFoodNumber;
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}