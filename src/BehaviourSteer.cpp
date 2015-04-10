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

	passedAnt1.moveVisualObjects(passedAnt1.getXPosition(),passedAnt1.getYPosition());
}

//void BehaviourSteer::update(Ant &passedAnt1){
//
//	passedAnt1.setPosition(Vector2D(passedAnt1.getXPosition() + passedAnt1.getDirection().getX() , passedAnt1.getYPosition() + passedAnt1.getDirection().getY()));
//}

void BehaviourSteer::moveup(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	//<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::movedown(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for x
	float yNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	//cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::moveleft(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(-1, 0);//picks a random number between -1 and 0 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	//cout<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::moveright(Ant &passedAnt1){
	float xNum = m_randomiser.getRandom(0, 1);//picks a random number between 0 and 1 for x
	float yNum = m_randomiser.getRandom(-1, 1);//picks a random number between -1 and 1 for y

	passedAnt1.getDirection().setX(xNum);
	passedAnt1.getDirection().setY(yNum);
	passedAnt1.setDirection(Vector2D(xNum,yNum));
	//<<passedAnt1.getDirection().getX()<<" "<<passedAnt1.getDirection().getY()<<endl;
}

void BehaviourSteer::WallCollision(Ant &passedAnt1){
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

//string BehaviourSteer::WallCol(Ant &passedAnt1){
//	if ((passedAnt1.getDirection().getX()>=-1 && passedAnt1.getDirection().getX()<=1) && (passedAnt1.getDirection().getY()>=0))//if moving up
//	{
//		return "moveDown";
//	}
//
//	if ((passedAnt1.getDirection().getX()>=-1 && passedAnt1.getDirection().getX()<=1) && (passedAnt1.getDirection().getY()<=0))//if moving down
//	{
//		return "moveUp";
//	}
//
//	if ((passedAnt1.getDirection().getY()>=-1 && passedAnt1.getDirection().getY()<=1) && (passedAnt1.getDirection().getX()>=0))//if moving left
//	{
//		return "moveRight";
//	}
//
//	if ((passedAnt1.getDirection().getY()>=-1 && passedAnt1.getDirection().getY()<=1) && (passedAnt1.getDirection().getX()<=0))//if moving right
//	{
//		return "moveLeft";
//	}
//}
//
//void BehaviourSteer::run(Ant &passedAnt1){
//	if(WallCol(passedAnt1) == "moveDown"){
//		movedown(passedAnt1);
//	}
//	else if(WallCol(passedAnt1) == "moveUp"){
//		moveup(passedAnt1);
//	}
//	else if(WallCol(passedAnt1) == "moveRight"){
//		moveright(passedAnt1);
//	}
//	else if(WallCol(passedAnt1) == "moveLeft"){
//		moveleft(passedAnt1);
//	}
//}