#include "ant.h"
#include "randomiser.h"
#include <stdlib.h>     //for using the function sleep
#include <Windows.h>
Ant::Ant()
{
	
}
Ant::Ant(Vector2D passedPosition, int width, int height) : AABB(passedPosition,  width,  height)
{
	antRadius = new Circle(getPosition(), 50,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
}
Ant::Ant(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor)
{
	antRadius = new Circle(getPosition(), 50,sf::Color::Green);// ant detection radius
	m_bCanMove = true;
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

void Ant::randomMovement()
{
	
	Randomiser* random = new Randomiser();

	float xNum = random->getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = random->getRandom(-1,1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);

	delete random;
	random = nullptr;
	/*delay so that a different random is generated*/
	Sleep(1000);
	srand (time(NULL));
	
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

	Randomiser random;

	float xNum = random.getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = random.getRandom(0,1);//picks a random number between 0 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}
void Ant::moveup()
{

	Randomiser random;

	float xNum = random.getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = random.getRandom(-1,0);//picks a random number between -1 and 0 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}
void Ant::moveleft()
{

	Randomiser random;

	float xNum = random.getRandom(-1,0);//picks a random number between -1 and 0 for x
	float yNum = random.getRandom(-1,1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
}
void Ant::moveright()
{
	Randomiser random;

	float xNum = random.getRandom(0,1);//picks a random number between 0 and 1 for x
	float yNum = random.getRandom(-1,1);//picks a random number between -1 and 1 for y

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
bool Ant::isMoveable()
{
	return m_bCanMove;
}
void Ant::draw(sf::RenderTarget& target /** Context for rendering */, 
sf::RenderStates states /** Primitive shpaes to render */) const
{

	target.draw(*antRadius);
	target.draw(rectangle);
}
