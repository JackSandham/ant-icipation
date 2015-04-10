#include <BehaviourFlee.h>

//using behaviours constructor
BehaviourFlee::BehaviourFlee() : Behaviour("FLEE")
{
	m_bAntColliding = false;
	
}

//require ants and collisionmanager.
void BehaviourFlee::run(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(antEaterInRadius(passedAnt1,passedEater,passedColMan))
	{
		avoidEater(passedAnt1,passedEater,passedColMan);
		
	}
	if(antEaterEats(passedAnt1,passedEater,passedColMan))
	{
		//death by anteater, send to hill
		passedAnt1.setPosition(passedAnt1.getStartPos());
	}
	else
	{
		passedAnt1.setFleeing(false);
		m_bAntColliding = false;
	}
}
bool BehaviourFlee::antEaterInRadius(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoCircleCollision(passedAnt1,*passedEater.getAntEaterInnerRadius()))
	{
		//cout<<"Flee Harder"<<endl;
		return true;
	}
	if(passedColMan.AABBtoCircleCollision(passedAnt1,*passedEater.getAntEaterOuterRadius()))
	{
		//cout<<"Flee"<<endl;
		return true;
	}
	else return false;
}

void BehaviourFlee::avoidEater(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	
		Vector2D m_vEaterDirection(passedAnt1.getPosition()-passedEater.getPosition());
		Vector2D m_vUnitDirection;
		m_vUnitDirection = m_vEaterDirection.unitVector();
		passedAnt1.setDirection(m_vUnitDirection);
		m_bAntColliding = true;
		passedAnt1.setFleeing(true);
}

bool BehaviourFlee::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
}

bool BehaviourFlee::antEaterEats(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoAABBCollision(passedAnt1,passedEater))
	{
		
		return true;
	}
	else
	{
		return false;
	}
}