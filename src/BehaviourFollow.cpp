#include <BehaviourFollow.h>

//using behaviours constructor
BehaviourFollow::BehaviourFollow() : Behaviour("FOLLOW")
{

}
/*
overriden run from behaviour, not sure how you want to use this here?
The run I have used requires ants and col-man.
What way were you thinking Nathan?
*/
void BehaviourFollow::run()
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
	if(passedColMan.getDistance()>=passedAnt1.getHalfHeight()*2)passedAnt2.setDirection(passedAnt1.getPosition()-passedAnt2.getPosition());
}