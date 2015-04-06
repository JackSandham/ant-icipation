/*
Basic ant follow behaviour, inherits behaviour.
Checks for two ants within eachothers radii.
The second ant then follows the first.
*/

#ifndef BEHAVIOURGATHER_H
#define BEHAVIOURGATHER_H

#include <string>
#include <ant.h>
#include <Food.h>
#include <Behaviour.h>
#include <CollisionsManager.h>
class BehaviourGather : public Behaviour
{
	public:
		BehaviourGather();

		bool antInRadius(Ant &passedAnt1, Food &passedFood, CollisionsManager &passedColMan);

		void seekFood(Ant &passedAnt1, Food &passedFood,CollisionsManager &passedColMan);
		void gatherFood(Ant &passedAnt1, Food &passedFood,CollisionsManager &passedColMan);
		void goHome(Ant &passedAnt1, Food &passedFood,CollisionsManager &passedColMan, AABB &antHill);
		virtual void run(Ant &passedAnt1, Food &passedFood, CollisionsManager &passedColMan);


	protected:

	private:
		

};

#endif