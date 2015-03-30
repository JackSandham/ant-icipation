#include "BehaviourSteer.h"

BehaviourSteer::BehaviourSteer() : Behaviour("STEER"){

}

void BehaviourSteer::randomDirection(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1,1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
}

void BehaviourSteer::move(Ant &passedAnt1){
	float mag = sqrt(m_vDirection.getX()*m_vDirection.getX()+m_vDirection.getY()*m_vDirection.getY());
	Vector2D constSpeed;
	float scalar= 1/mag;
	if(mag!=0)
	{
		constSpeed.setX(m_vDirection.getX()*scalar);
		constSpeed.setY(m_vDirection.getY()*scalar);

	}
	passedAnt1.setPosition(Vector2D(passedAnt1.getXPosition() + constSpeed.getX(), passedAnt1.getYPosition() + constSpeed.getY()));

	//moves the ant based on the direction of the numers generated

	passedAnt1.moveVisualObjects(passedAnt1.getXPosition(),passedAnt1.getYPosition());
}

void BehaviourSteer::moveup(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::movedown(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::moveleft(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::moveright(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	m_vDirection.setX(xNum);
	m_vDirection.setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::WallCollision(Ant &passedAnt1){
	if ((m_vDirection.getX()>=-1 && m_vDirection.getX()<=1) && (m_vDirection.getY()>=0))//if moving up
	{
		movedown(passedAnt1);
	}

	if ((m_vDirection.getX()>=-1 && m_vDirection.getX()<=1) && (m_vDirection.getY()<=0))//if moving down
	{
		moveup(passedAnt1);
	}

	if ((m_vDirection.getY()>=-1 && m_vDirection.getY()<=1) && (m_vDirection.getX()>=0))//if moving left
	{
		moveright(passedAnt1);
	}

	if ((m_vDirection.getY()>=-1 && m_vDirection.getY()<=1) && (m_vDirection.getX()<=0))//if moving right
	{
		moveleft(passedAnt1);
	}
}