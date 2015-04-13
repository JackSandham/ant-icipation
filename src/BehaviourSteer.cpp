#include "BehaviourSteer.h"

BehaviourSteer::BehaviourSteer() : Behaviour("STEER"){

}

void BehaviourSteer::randomDirection(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::move(Ant &passedAnt1){
	float mag = sqrt(passedAnt1.getDirection().getX()*passedAnt1.getDirection().getX()+passedAnt1.getDirection().getY()*passedAnt1.getDirection().getY());
	Vector2D constSpeed;
	float scalar= 1/mag;
	if(mag!=0)
	{
		constSpeed.setX(passedAnt1.getDirection().getX()*scalar);
		constSpeed.setY(passedAnt1.getDirection().getY()*scalar);

	}
	passedAnt1.setPosition(Vector2D(passedAnt1.getXPosition() + constSpeed.getX(), passedAnt1.getYPosition() + constSpeed.getY()));

	//moves the ant based on the direction of the numers generated

}

void BehaviourSteer::moveup(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::movedown(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::moveleft(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::moveright(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::run(Ant &passedAnt1){
	if ((passedAnt1.getDirection().getX()>=-1 && passedAnt1.getDirection().getX()<=1) && (passedAnt1.getDirection().getY()>=0))//if moving up
	{
		movedown(passedAnt1);
	}

	if ((passedAnt1.getDirection().getX()>=-1 && passedAnt1.getDirection().getX()<=1) && (passedAnt1.getDirection().getY()<=0))//if moving down
	{
		moveup(passedAnt1);
	}

	if ((passedAnt1.getDirection().getY()>=-1 && passedAnt1.getDirection().getY()<=1) && (passedAnt1.getDirection().getX()>=0))//if moving left
	{
		moveright(passedAnt1);
	}

	if ((passedAnt1.getDirection().getY()>=-1 && passedAnt1.getDirection().getY()<=1) && (passedAnt1.getDirection().getX()<=0))//if moving right
	{
		moveleft(passedAnt1);
	}
}