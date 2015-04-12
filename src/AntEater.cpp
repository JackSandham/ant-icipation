#include "antEater.h"
#include <stdlib.h>
#include <Windows.h>

AntEater::AntEater()
{
}

AntEater::AntEater(Vector2D passedPosition, int width, int height) : AABB(passedPosition, width, height)
{
	m_fDetectionRadius = 160;
	anteaterInnerRadius = new Circle(getPosition(), 125);
	anteaterOuterRadius = new Circle(getPosition(), m_fDetectionRadius);
	m_bRadiusVisible = true;
	m_bCanMove = true;

	float fWidth = (float)width;
	float fHeight = (float)height;

	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("ant_eater"));
	m_sprite.setScale(fWidth / tm->getTexture("ant_eater")->getSize().x, fHeight / tm->getTexture("ant_eater")->getSize().y);
	m_sprite.setPosition(passedPosition.getX() + 300, passedPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);

	changeTargetPosition();
}

void AntEater::update()
{
	setMin();
	setMax();
}

void AntEater::moveVisualObjects(float xPos, float yPos)
{
	m_sprite.setPosition(xPos + 300, yPos + 100);
	float rotation = atan2(m_vDirection.getY(), m_vDirection.getX()) * (180 / 3.14159265) + 90;
	m_sprite.setRotation(rotation);
	rectangle.setRotation(rotation);
	anteaterOuterRadius->setPosition(Vector2D(xPos, yPos));
	anteaterInnerRadius->setPosition(Vector2D(xPos, yPos));
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

void AntEater::setColliding(bool bColliding)
{
	m_bAntColliding = bColliding;
}

bool AntEater::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
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

Circle* AntEater::getAntEaterOuterRadius()
{
	return anteaterOuterRadius;
}

Circle* AntEater::getAntEaterInnerRadius()
{
	return anteaterInnerRadius;
}

/*void AntEater::setFood(bool bPassedFood)
{
	m_bHasFood=bPassedFood;
}*/

bool AntEater::getFood()
{
	return m_bHasFood;
}

void AntEater::wander()
{
	// Note that 20 units is fairly arbitrary. The value can just be changed until it "feels" right
	if (distanceTo(m_vTargetPosition) < 20)
	{
		changeTargetPosition();
	}
	else
	{
		moveTowards(m_vTargetPosition);
	}
}

float AntEater::getDetectionRadius() const
{
	return m_fDetectionRadius;
}

float AntEater::distanceTo(Vector2D vPos)
{
	float dX = vPos.getX() - getPosition().getX();
	float dY = vPos.getY() - getPosition().getY();
	return std::sqrt((dX * dX) + (dY * dY));
}

void AntEater::moveTowards(Vector2D vPos)
{
	float dX = vPos.getX() - getPosition().getX();
	float dY = vPos.getY() - getPosition().getY();
	m_vDirection = Vector2D(dX, dY);
	m_vDirection.normalise();
	
	Vector2D newPos = getPosition();
	newPos.setX(newPos.getX() + (m_vDirection.getX() * 1));
	newPos.setY(newPos.getY() + (m_vDirection.getY() * 1));

	setPosition(newPos);
	moveVisualObjects(newPos.getX(), newPos.getY());
}

void AntEater::changeTargetPosition()
{
	m_vTargetPosition = Vector2D(0, 0);
	m_vTargetPosition.setX(m_randomiser.getRandom(200, 1300));
	m_vTargetPosition.setY(m_randomiser.getRandom(0, 900));	
}

void AntEater::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}