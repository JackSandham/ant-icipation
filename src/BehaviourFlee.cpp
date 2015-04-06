#include <BehaviourFlee.h>

//using behaviours constructor
BehaviourFlee::BehaviourFlee() : Behaviour("FLEE")
{
	m_bAntColliding = false;
}

//require ants and collisionmanager.
void BehaviourFlee::run(Ant &passedAnt1, Eater &passedEater, CollisionsManager &passedColMan)
{
	if(antEaterInRadius(passedAnt1,passedEater,passedColMan))
	{
		avoidEater(passedAnt1,passedEater,passedColMan);
		
	}
	else m_bAntColliding = false;
}
bool BehaviourFlee::antEaterInRadius(Ant &passedAnt1, Eater &passedEater, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoCircleCollision(passedEater,*passedAnt1.getAntRadius())) return true;
	else return false;
}

void BehaviourFlee::avoidEater(Ant &passedAnt1, Eater &passedEater, CollisionsManager &passedColMan)
{
	if(passedAnt1.getDirection().dotProduct(passedColMan.getNormal()) <0)
	{
		passedColMan.correctPosition(passedAnt1);
		steerBehaviour.WallCollision(passedAnt1);
		m_bAntColliding = true;
		
	}
	else m_bAntColliding = false;
	
}

bool BehaviourFlee::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
}