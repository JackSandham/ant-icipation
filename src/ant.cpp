#include "ant.h"
#include <stdlib.h>     //for using the function sleep
#include <Windows.h>

Ant::Ant()
{
}

Ant::Ant(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	antRadius = new Circle(getPosition(), 100,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
	Update();
}

Ant::Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor)
{
	antRadius = new Circle(getPosition(), 100,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
	Update();
}

void Ant::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
}

//This function was created to move the rectangle position and the ant radius position.
//This was needed as the rectangle object is protected and the circle radius object is private.
//This means that they are only changed in this function.
void Ant::moveVisualObjects(float xPos, float yPos){
	rectangle.setPosition(xPos,yPos);
	antRadius->setPosition(Vector2D(xPos,yPos));
}

void Ant::setMovable(bool bPassedMove)
{
	m_bCanMove = bPassedMove;
}

void Ant::setDirection(Vector2D passedVector)
{
	m_vDirection = passedVector;
}

void Ant::setRadiusVisibility(bool bPassedVisibility)
{
	m_bRadiusVisible = bPassedVisibility;
}

bool Ant::isMoveable()
{
	return m_bCanMove;
}

bool Ant::radiusIsVisible()
{
	return m_bRadiusVisible;
}

Vector2D Ant::getDirection()
{
	return m_vDirection;
}

void Ant::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bRadiusVisible)
	{
		target.draw(*antRadius);
	}
	target.draw(rectangle);
}

Circle* Ant::getAntRadius()
{
	return antRadius;
}