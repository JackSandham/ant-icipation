#include "antEater.h"
#include <stdlib.h>
#include <Windows.h>

AntEater::AntEater()
{
}

AntEater::AntEater(Vector2D passedPosition, int width, int height) : AABB(passedPosition, width, height)
{
	anteaterInnerRadius = new Circle(getPosition(), 125);
	anteaterOuterRadius = new Circle(getPosition(), 160);
	m_bRadiusVisible = true;
	m_bCanMove = true;
	Update();

	float fWidth = (float)width;
	float fHeight = (float)height;

	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("ant_eater"));
	m_sprite.setScale(fWidth / tm->getTexture("ant_eater")->getSize().x, fHeight / tm->getTexture("ant_eater")->getSize().y);
	m_sprite.setPosition(passedPosition.getX() + 300, passedPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);
}

void AntEater::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y;
	m_fLeft = rectangle.getPosition().x;
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;
	m_fTop = rectangle.getPosition().y;
	setMin();
	setMax();
}

void AntEater::moveVisualObjects(float xPos, float yPos)
{
	m_sprite.setPosition(xPos + 300, yPos + 100);
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

void AntEater::setFood(bool bPassedFood)
{
	m_bHasFood=bPassedFood;
}

bool AntEater::getFood()
{
	return m_bHasFood;
}

void AntEater::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}