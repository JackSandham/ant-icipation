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
	m_bIsCarryingFood = false;
	m_pFood = nullptr;
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

void Ant::update(AntEater &passedAntEater, CollisionsManager &passedColMan)
{
	setMin();
	setMax();
	facingEater(passedAntEater,passedColMan);

	if (isCarryingFood())
	{
		m_pFood->setPosition(getPosition());
	}
}

void Ant::setPosition(Vector2D pos)
{
	m_vPosition = pos;
	m_sprite.setPosition(pos.getX() + 300, pos.getY() + 100);
	m_sprite.setRotation(atan2(m_vDirection.getY(), m_vDirection.getX()) * (180 / 3.14159265) + 90);
	rectangle.setPosition(pos.getX(), pos.getY());
	antRadius->setPosition(Vector2D(pos.getX(), pos.getY()));
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

Food* Ant::getFood()
{
	return m_pFood;
}

void Ant::moveTowards(Vector2D vPos)
{
	float dX = vPos.getX() - getPosition().getX();
	float dY = vPos.getY() - getPosition().getY();
	m_vDirection = Vector2D(dX, dY);
	m_vDirection.normalise();

	Vector2D newPos = getPosition();
	newPos.setX(newPos.getX() + (m_vDirection.getX() * 0.65));
	newPos.setY(newPos.getY() + (m_vDirection.getY() * 0.65));

	setPosition(newPos);
}

float Ant::getFoodDetectionRadius()
{
	return 100;
}

float Ant::getCollectionRange()
{
	return 10;
}

void Ant::assignFood(Food* f)
{
	f->setCollidable(false);
	m_pFood = f;
	m_bIsCarryingFood = true;
}

bool Ant::isCarryingFood()
{
	return m_bIsCarryingFood;
}

void Ant::dropFood()
{
	m_pFood->setCollidable(true);
	m_pFood = nullptr;
	m_bIsCarryingFood = false;
}