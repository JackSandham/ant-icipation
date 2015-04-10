#include "ant.h"
#include <stdlib.h>     //for using the function sleep
#include <Windows.h>

Ant::Ant()
{
}

Ant::Ant(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	m_vStartPos = passedPosition;
	antRadius = new Circle(getPosition(), 75);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
	m_bHasFood = false;
	m_bAntColliding = false;
	m_bFleeing = false;
	m_bFacingEater = false;
	//Update();

	float fWidth = (float)width;
	float fHeight = (float)height;

	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("ant"));
	m_sprite.setScale(fWidth / tm->getTexture("ant")->getSize().x, fHeight / tm->getTexture("ant")->getSize().y);
	m_sprite.setPosition(passedPosition.getX() + 300, passedPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);
}

void Ant::Update(AntEater &passedAntEater, CollisionsManager &passedColMan)
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
	setMin();
	setMax();
	facingEater(passedAntEater,passedColMan);
	if(antEaterEats(passedAntEater,passedColMan))
	{
		//death by anteater, send to hill
		setPosition(getStartPos());
	}
}

//This function was created to move the rectangle position and the ant radius position.
//This was needed as the rectangle object is protected and the circle radius object is private.
//This means that they are only changed in this function.
void Ant::moveVisualObjects(float xPos, float yPos)
{
	m_sprite.setPosition(xPos + 300, yPos + 100);
	m_sprite.setRotation(atan2(m_vDirection.getY(), m_vDirection.getX()) * (180 / 3.14159265) + 90);
	rectangle.setPosition(xPos,yPos);
	antRadius->setPosition(Vector2D(xPos,yPos));
}

void Ant::facingEater(AntEater &passedAntEater, CollisionsManager &passedColMan)
{
	if(getDirection().dotProduct(passedColMan.getNormal()) > 0)
	{
		setFacingEater(true);
	}
	else
	{
		setFacingEater(false);
	}
}

bool Ant::antEaterEats(AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoAABBCollision(*this,passedEater))
	{
		
		return true;
	}
	else
	{
		return false;
	}
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

void Ant::setFacingEater(bool bFacing)
{
	m_bFacingEater = bFacing;
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

bool Ant::isFacingEater()
{
	if(m_bFacingEater)
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
int Ant::getNumber()
{
	return m_iNumber;
}
void Ant::setNumber(int iPassedNumber)
{
	m_iNumber=iPassedNumber;
}

void Ant::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}