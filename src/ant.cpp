#include "ant.h"
#include <stdlib.h>     //for using the function sleep
#include <Windows.h>

Ant::Ant()
{
}

Ant::Ant(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	m_vStartPos = passedPosition;
	antRadius = new Circle(getPosition(), 75,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
	m_bHasFood = false;
	m_bAntColliding = false;
	m_bFleeing = false;
	m_bFacingWall = false;
	Update();
}

Ant::Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor)
{
	m_vStartPos = passedPosition;
	antRadius = new Circle(getPosition(), 75,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
	m_bHasFood = false;
	m_bFleeing = false;
	m_bFacingWall = false;
	Update();
}

void Ant::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
	setMin();
	setMax();
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

void Ant::setColliding(bool bColliding)
{
	m_bAntColliding = bColliding;
}

void Ant::setFleeing(bool bFleeing)
{
	m_bFleeing = bFleeing;
}

void Ant::setFacingWall(bool bFacing)
{
	m_bFacingWall = bFacing;
}


bool Ant::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
}

bool Ant::isFleeing()
{
	if(m_bFleeing)
	{
		return true;
	}
	else return false;
}

bool Ant::isFacingWall()
{
	if(m_bFacingWall)
	{
		return true;
	}
	else return false;
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

Vector2D Ant::getStartPos()
{
	return m_vStartPos;
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

void Ant::setFood(bool bPassedFood)
{
	m_bHasFood=bPassedFood;
}

bool Ant::getFood()
{
	return m_bHasFood;
}