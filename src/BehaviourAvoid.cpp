#include <BehaviourAvoid.h>

//using behaviours constructor
BehaviourAvoid::BehaviourAvoid() : Behaviour("AVOID")
{
	m_bAntColliding = false;
}

//require ants and collisionmanager.
void BehaviourAvoid::run(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan)
{
	if(obstacleInRadius(passedAnt1,passedBackObstacles,passedColMan))
	{
		avoidObstacle(passedAnt1,passedBackObstacles,passedColMan);
		
	}
	else m_bAntColliding = false;
}
bool BehaviourAvoid::obstacleInRadius(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoCircleCollision(passedBackObstacles,*passedAnt1.getAntRadius())) return true;
	else return false;
}

void BehaviourAvoid::avoidObstacle(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan)
{
	if(passedAnt1.getDirection().dotProduct(passedColMan.getNormal()) <0)
	{
		passedColMan.correctPosition(passedAnt1);
		passedAnt1.WallCollision();
		m_bAntColliding = true;
		
	}
	else m_bAntColliding = false;
	
}

bool BehaviourAvoid::isColliding()
{
	if(m_bAntColliding)
	{
		return true;
	}
	else return false;
}