#include <BehaviourFollow.h>

//using behaviours constructor
BehaviourFollow::BehaviourFollow() : Behaviour("FOLLOW")
{

}

//require ants and collisionmanager.
void BehaviourFollow::run(Ant &passedAnt1, Ant &passedAnt2, CollisionsManager &passedColMan)
{
	if(antInRadius(passedAnt1,passedAnt2,passedColMan))
	{
		followAnt(passedAnt1,passedAnt2,passedColMan);
		
	}
}
bool BehaviourFollow::antInRadius(Ant &passedAnt1, Ant &passedAnt2, CollisionsManager &passedColMan)
{
	if(passedColMan.CircletoCircleCollision(*passedAnt1.getAntRadius(),*passedAnt2.getAntRadius())) return true;
	else return false;
}

void BehaviourFollow::followAnt(Ant &passedAnt1, Ant &passedAnt2, CollisionsManager &passedColMan)
{
	//check distance between them.
	passedColMan.AABBtoAABBCollision(passedAnt1,passedAnt2);
	//One ant behind the other
	if(passedColMan.getDistance()>=passedAnt1.getHalfHeight()*2)
	{
		Vector2D m_vFirstAntDirection(passedAnt1.getPosition()-passedAnt2.getPosition());
		Vector2D m_vUnitDirection;
		m_vUnitDirection = m_vFirstAntDirection.unitVector();
		passedAnt2.setDirection(m_vUnitDirection);
	}
}