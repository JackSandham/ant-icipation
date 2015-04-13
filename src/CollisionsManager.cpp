#include "collisionsmanager.h"
#include <iostream>


CollisionsManager::CollisionsManager()
{
	//default constructor
}

bool CollisionsManager::AABBtoCircleCollision(AABB &aabb,Circle &circle)
{

	Vector2D CirclePos = circle.getPosition()-aabb.getPosition(); //create a temporary circle position with the balls position minus the box's position
	Vector2D CirclePos2 = CirclePos; //create a copy of the circles position
	Vector2D RectanglePos; 
	RectanglePos.setX(0);
	RectanglePos.setY(0); //create a temporary vector for the rectangles popsition with the values (0,0)

	Vector2D Distance; 
	Distance = (CirclePos - RectanglePos); //create a distance vector with the values of the new circle position minus the rectangle position


	Vector2D clamp; //create a vector for a clamp

	if(Distance.getX() >= 0)clamp.setX(std::min(Distance.getX(),aabb.getHalfWidth()));
	if(Distance.getX() < 0) clamp.setX(std::max(Distance.getX(),-aabb.getHalfWidth()));
	if(Distance.getY() >= 0)clamp.setY(std::min(Distance.getY(),aabb.getHalfHeight())); 
	if(Distance.getY() < 0) clamp.setY(std::max(Distance.getY(),-aabb.getHalfHeight())); //gets the value for the clamp vector

	Vector2D vDifference;

	vDifference =  Distance - clamp; //gets the difference of the distance minus the clamp

	float fmagnitude = sqrt(pow(vDifference.getX(), 2) +(pow(vDifference.getY(),2))); //gets the magnitude 

	m_fFinalDistance = (fmagnitude - circle.getRadius()); //gets the distance between the ball and box
	m_Normal = vDifference.unitVector();
	if (m_fFinalDistance <=0) //if distance <= 0, a collision has happened
	{
		return true;
	}	
	else
	{
		return false;
	}
}


bool CollisionsManager::AABBtoAABBCollision(AABB& aabb, AABB& aabb2)
{
	Vector2D tempVec = aabb.getPosition()-aabb2.getPosition();
	m_fFinalDistance = tempVec.getMagnitude()-aabb.getHalfHeight();
	if(aabb.getMax().getX() < aabb2.getMin().getX()  || aabb.getMin().getX() > aabb2.getMax().getX()) return false;
	if(aabb.getMax().getY() < aabb2.getMin().getY()  || aabb.getMin().getY() > aabb2.getMax().getY()) return false;
	return true;
}


bool CollisionsManager::OBBtoCircleCollision(OBB &obb, Circle &circle)
{
	float radians = obb.getAngle()/(180/3.14); //converts the box' angle to radians

	Vector2D CirclePos = circle.getPosition()-obb.getPosition(); //create a temporary circle position with the balls position minus the box's position
	Vector2D CirclePos2 = CirclePos; //create a copy of the circles position
	Vector2D RectanglePos; 
	RectanglePos.setX(0);
	RectanglePos.setY(0); //create a temporary vector for the rectangles popsition with the values (0,0)

	CirclePos.setX((CirclePos.getX()*(cos(radians))) + (CirclePos.getY()*(sin(radians)))); 

	CirclePos.setY((CirclePos2.getX()*(-sin(radians))) + (CirclePos2.getY()*(cos(radians)))); //apply a rotation matrix to the circles position



	Vector2D Distance; 
	Distance = (CirclePos - RectanglePos); //create a distance vector with the values of the new circle position minus the rectangle position


	Vector2D clamp; //create a vector for a clamp

	if(Distance.getX() >= 0)clamp.setX(std::min(Distance.getX(),obb.getHalfWidth()));
	if(Distance.getX() < 0) clamp.setX(std::max(Distance.getX(),-obb.getHalfWidth()));
	if(Distance.getY() >= 0)clamp.setY(std::min(Distance.getY(),obb.getHalfHeight())); 
	if(Distance.getY() < 0) clamp.setY(std::max(Distance.getY(),-obb.getHalfHeight())); //gets the value for the clamp vector


	Vector2D vDifference;

	vDifference =  Distance - clamp; //gets the difference of the distance minus the clamp



	float fmagnitude = sqrt(pow(vDifference.getX(), 2) +(pow(vDifference.getY(),2))); //gets the magnitude 

	m_fFinalDistance = (fmagnitude - circle.getRadius()); //gets the distance between the ball and box

	Vector2D vDifferenceRotated;


	vDifferenceRotated.setX((vDifference.getX()*(cos(radians))) + (vDifference.getY()*(-sin(radians))));
	vDifferenceRotated.setY((vDifference.getX()*(sin(radians))) + (vDifference.getY()*(cos(radians)))); //rotate the difference vector back

	m_Normal.setValues(vDifferenceRotated.getX(),vDifferenceRotated.getY());	//calculates the normal
	m_Normal.unitVector();		


	if (m_fFinalDistance <=0) //if distance <= 0, a collision had happened
	{
		return true;			
	}
	else
	{
		return false;
	}
}

bool CollisionsManager::CircletoCircleCollision(Circle &circle, Circle &circle2)
{
	Vector2D vDistance = circle.getPosition()-circle2.getPosition();

	float mag = std::sqrt(vDistance.getX() * vDistance.getX()  + vDistance.getY()  * vDistance.getY() );

	float radii = circle.getRadius()+circle2.getRadius();

	m_Normal = vDistance.unitVector();
	m_fFinalDistance = mag - radii;

	if(m_fFinalDistance<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CollisionsManager::correctPosition(Shape &passedShape)
{
	//penetration depth
	float fPercent = 0.5f;
	float fSlop = 0.1f;
	//Calculate the penetration depth minus the slop
	float fPDMinusSlop = m_fFinalDistance -fSlop;
	//Max between pdMinusSlop and 0
	float fMax = fPDMinusSlop>0 ? fPDMinusSlop : 0;
	//Calculate c position
	float cPosX = ((fMax/(1))*fPercent)*(m_Normal.getX());
	float cPosY = ((fMax/(1))*fPercent)*(m_Normal.getY());
	Vector2D cPos(cPosX,cPosY);
	Vector2D newPos = passedShape.getPosition() - (cPos*1);
	passedShape.setPosition(newPos);
}

Vector2D CollisionsManager::getNormal()
{
	return m_Normal;
}
float CollisionsManager::getDistance()
{
	return m_fFinalDistance;
}