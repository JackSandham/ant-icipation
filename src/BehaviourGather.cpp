#include <BehaviourGather.h>

//using behaviours constructor
BehaviourGather::BehaviourGather() : Behaviour("GATHER")
{

}

//require ants and collisionmanager.
void BehaviourGather::run(Ant &passedAnt1, Food &passedFood, CollisionsManager &passedColMan)
{
	if(antInRadius(passedAnt1,passedFood,passedColMan))
	{
		seekFood(passedAnt1,passedFood,passedColMan);
		
	}
}
bool BehaviourGather::antInRadius(Ant &passedAnt1, Food &passedFood, CollisionsManager &passedColMan)
{
	if(passedColMan.CircletoCircleCollision(*passedAnt1.getAntRadius(),*passedFood.getFoodRadius())) return true;
	else return false;
}

void BehaviourGather::seekFood(Ant &passedAnt1, Food &passedFood, CollisionsManager &passedColMan)
{
	//check distance between them.
	passedColMan.AABBtoAABBCollision(passedAnt1,passedFood);
	//One ant behind the other
	if(passedColMan.getDistance()>=passedAnt1.getHalfHeight())
	{

		Vector2D vec = Vector2D(passedFood.getPosition() - passedAnt1.getPosition());
		float xPos = vec.getX()/vec.getMagnitude();
		float yPos = vec.getY()/vec.getMagnitude();

		vec.setX(xPos);
		vec.setY(yPos);

		float mag = vec.getMagnitude();



		float scalar= 1/mag;
		if(mag!=0)
		{
			vec.setX(xPos*scalar);
			vec.setY(yPos*scalar);

		}

	//moves the ant based on the direction of the numers generated


		passedAnt1.setDirection(vec);
	}

	
}


void BehaviourGather::gatherFood(Ant &passedAnt1, Food &passedFood,CollisionsManager &passedColMan)
{
	if(passedColMan.AABBtoAABBCollision(passedAnt1,passedFood)==true)
	{
		passedFood.setCollidable(false);
		passedFood.setPosition(passedAnt1.getPosition());
	}
}