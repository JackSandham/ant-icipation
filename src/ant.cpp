#include "ant.h"


Ant::Ant()
{
	
}
void Ant::Update()
{
	

	m_fBottom = Rectangle.getPosition().y + Rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = Rectangle.getPosition().x; //calculates the left edge
	m_fRight = Rectangle.getPosition().x + Rectangle.getSize().x;//calculates the right edge
	m_fTop = Rectangle.getPosition().y;//calculates the top edge

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

	direction.x=xNum;
	direction.y=yNum;

}

void Ant::move()
{
	m_vPosition.x+=direction.x;
	m_vPosition.y+=direction.y;

	//moves the ant based on the direction of the numers generated

	Rectangle.setPosition(m_vPosition);


}


void Ant::movedown()
{
	float xNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for x
	float yNum = ((float)rand())/RAND_MAX;//picks a random number between 0 and 1 for y

	direction.x=xNum;
	direction.y=yNum;
}
void Ant::moveup()
{
	float xNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for x
	float yNum = -1*((float)rand())/RAND_MAX;//picks a random number between -1 and 0 for y

	direction.x=xNum;
	direction.y=yNum;
}
void Ant::moveleft()
{
	float xNum = -1*((float)rand())/RAND_MAX;//picks a random number between -1 and 0 for x
	float yNum = -1+2*((float)rand())/RAND_MAX;;//picks a random number between -1 and 1 for y

	direction.x=xNum;
	direction.y=yNum;
}
void Ant::moveright()
{
	float xNum = ((float)rand())/RAND_MAX;//picks a random number between 0 and 1 for x
	float yNum = -1+2*((float)rand())/RAND_MAX;//picks a random number between -1 and 1 for y

	direction.x=xNum;
	direction.y=yNum;
}
