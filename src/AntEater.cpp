#include "antEater.h"
#include <stdlib.h>
#include <Windows.h>

AntEater::AntEater()
{
}

AntEater::AntEater(Vector2D passedPosition, int width, int height) : AABB(passedPosition, width, height)
{
	anteaterRadius = new Circle(getPosition(), 150, sf::Color::Yellow);
	m_bRadiusVisible = true;
	m_bCanMove = true;
	Update();
}
AntEater::AntEater(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition, width, height, passedColor)
{
 anteaterRadius = new Circle(getPosition(), 150, sf::Color::Yellow);
 m_bRadiusVisible = true;
 m_bCanMove = true;
 Update();
}
void AntEater::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y;
	m_fLeft = rectangle.getPosition().x;
	m_fRight = rectangle.getPosition().x;
	m_fTop = rectangle.getPosition().y;
	setMin();
	setMax();
}

void AntEater::moveVisualObjects(float xPos, float yPos)
{
	rectangle.setPosition(xPos,yPos);
	anteaterRadius->setPosition(Vector2D(xPos,yPos));
}

void AntEater::setMovable(bool bPassedMove)
{
	m_bCanMove = bPassedMove;
}
void AntEater::setDirection(Vector2D passedVector)
{
	m_vDirection = passedVector;
}

void AntEater::setRadiusVisibility(bool bPassedVisibility)
{
	m_bRadiusVisible = bPassedVisibility;
}

bool AntEater::isMoveable()
{
	return m_bCanMove;
}

bool AntEater::radiusIsVisible()
{
	return m_bRadiusVisible;
}

Vector2D AntEater::getDirection()
{
	return m_vDirection;
}

void AntEater::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bRadiusVisible)
	{
		target.draw(*anteaterRadius);
	}
	target.draw(rectangle);
}
Circle* AntEater::getAntEaterRadius()
{
	return anteaterRadius;
}

void AntEater::setFood(bool bPassedFood)
{
	m_bHasFood=bPassedFood;
}

bool AntEater::getFood()
{
	return m_bHasFood;
}

