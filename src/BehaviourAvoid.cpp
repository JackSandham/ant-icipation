#include <BehaviourAvoid.h>

//using behaviours constructor
BehaviourAvoid::BehaviourAvoid() : Behaviour("AVOID")
{
	
}

//require ants and collisionmanager.
void BehaviourAvoid::run(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan)
{
	if(obstacleInRadius(passedAnt1,passedBackObstacles,passedColMan))
	{
		avoidObstacle(passedAnt1,passedBackObstacles,passedColMan);
		passedAnt1.setColliding(true);
	}
	
	else passedAnt1.setColliding(false);
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
		//passedAnt1.setFacingWall(true);
		passedColMan.correctPosition(passedAnt1);
		steerBehaviour.WallCollision(passedAnt1);
		//steerBehaviour.WallCol(passedAnt1);
		
	}
	else
	{
		//passedAnt1.setFacingWall(false);
		passedAnt1.setColliding(false);
	}
	
}

