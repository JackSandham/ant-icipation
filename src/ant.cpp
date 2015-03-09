#include "ant.h"

Ant::Ant()
{
	
}
void Ant::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
}


void Ant::WallCollision(Ant ant)
{
	if(m_fLeft<=1+getHalfWidth()) //if the ant collides with the left side of the screen
	{
		moveright();
	}
	if(m_fRight>=800+getHalfWidth())//if the ant collides with the right side of the screen
	{
		moveleft();
	}
	if(m_fTop<=1+getHalfHeight())//if the ant collides with the top of the screen
	{
		movedown();
	}
	if(m_fBottom>=600+getHalfHeight())//if the ant collides with the bottom of the screen
	{
		moveup();
	}
}

void Ant::randomMovement()
{
	float xNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for x
	float yNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for y

	m_vDirection.x=xNum;
	m_vDirection.y=yNum;
}

void Ant::move()
{
	m_vPosition.x+=m_vDirection.x;
	m_vPosition.y+=m_vDirection.y;

	//moves the ant based on the direction of the numers generated

	rectangle.setPosition(m_vPosition);
}


void Ant::movedown()
{
	float xNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for x
	float yNum = ((float)rand())/RAND_MAX;//picks a random number between 0 and 1 for y

	m_vDirection.x=xNum;
	m_vDirection.y=yNum;
}
void Ant::moveup()
{
	float xNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for x
	float yNum = -1*((float)rand())/RAND_MAX;//picks a random number between -1 and 0 for y

	m_vDirection.x=xNum;
	m_vDirection.y=yNum;
}
void Ant::moveleft()
{
	float xNum = -1*((float)rand())/RAND_MAX;//picks a random number between -1 and 0 for x
	float yNum = -1+2*((float)rand())/RAND_MAX;;//picks a random number between -1 and 1 for y

	m_vDirection.x=xNum;
	m_vDirection.y=yNum;
}
void Ant::moveright()
{
	float xNum = ((float)rand())/RAND_MAX;//picks a random number between 0 and 1 for x
	float yNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for y

	m_vDirection.x=xNum;
	m_vDirection.y=yNum;
}
