#include <BehaviourFlee.h>

//using behaviours constructor
BehaviourFlee::BehaviourFlee() : Behaviour("FLEE")
{
	m_bAntColliding = false;
	m_bFleeing = false;
}

//require ants and collisionmanager.
void BehaviourFlee::run(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(antEaterInRadius(passedAnt1,passedEater,passedColMan))
	{
		avoidEater(passedAnt1,passedEater,passedColMan);
		
	}
	else
	{
		m_bFleeing = false;
		m_bAntColliding = false;
	}
}
bool BehaviourFlee::antEaterInRadius(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoCircleCollision(passedEater,*passedAnt1.getAntRadius())) return true;
	else return false;
}

void BehaviourFlee::avoidEater(Ant &passedAnt1, AntEater &passedEater, CollisionsManager &passedColMan)
{
	
		Vector2D m_vEaterDirection(passedAnt1.getPosition()-passedEater.getPosition());
		Vector2D m_vUnitDirection;
		m_vUnitDirection = m_vEaterDirection.unitVector();
		passedAnt1.setDirection(m_vUnitDirection);
		m_bAntColliding = true;
		m_bFleeing = true;
	
	
}

bool BehaviourFlee::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
}
bool BehaviourFlee::isFleeing()
{
	if(m_bFleeing)
	{
		return true;
	}
	else return false;
}