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
}

Ant::Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor)
{
	antRadius = new Circle(getPosition(), 100,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
	m_bRadiusVisible = true;
}

void Ant::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
}

void Ant::WallCollision()
{
	/*if(m_fLeft<=1+getHalfWidth()) //if the ant collides with the left side of the screen
	{
		moveright();
	}
	
	if(m_fRight>=1000+getHalfWidth())//if the ant collides with the right side of the screen
	{
		moveleft();
	}
	if(m_fTop<=1+getHalfHeight())//if the ant collides with the top of the screen
	{
		movedown();
	}
	if(m_fBottom>=1000+getHalfHeight())//if the ant collides with the bottom of the screen
	{
		moveup();
	}*/

	if ((m_vDirection.getX()>=-1 && m_vDirection.getX()<=1) && (m_vDirection.getY()>=0))//if moving up
	{
		
		movedown();
	}

	if ((m_vDirection.getX()>=-1 && m_vDirection.getX()<=1) && (m_vDirection.getY()<=0))//if moving down
	{
		
		moveup();
	}

	if ((m_vDirection.getY()>=-1 && m_vDirection.getY()<=1) && (m_vDirection.getX()>=0))//if moving left
	{
		
		moveright();
	}

	if ((m_vDirection.getY()>=-1 && m_vDirection.getY()<=1) && (m_vDirection.getX()<=0))//if moving right
	{
		
		moveleft();
	}
	
}

void Ant::randomDirection()
{
	float xNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);	
}

void Ant::move()
{
	float mag = sqrt(m_vDirection.getX()*m_vDirection.getX()+m_vDirection.getY()*m_vDirection.getY());
	Vector2D constSpeed;
	float scalar= 1/mag;
	if(mag!=0)
	{
		constSpeed.setX(m_vDirection.getX()*scalar);
		constSpeed.setY(m_vDirection.getY()*scalar);

	}
	m_vPosition.setX(m_vPosition.getX()+constSpeed.getX());
	m_vPosition.setY(m_vPosition.getY()+constSpeed.getY());

	//moves the ant based on the direction of the numers generated

	rectangle.setPosition(m_vPosition.getX(),m_vPosition.getY());
	antRadius->move(getPosition()); //update detection radius to ant
}

void Ant::movedown()
{
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}

void Ant::moveup()
{
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}

void Ant::moveleft()
{
	float xNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}

void Ant::moveright()
{
	float xNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}

Circle* Ant::getAntRadius()
{
	return antRadius;
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
