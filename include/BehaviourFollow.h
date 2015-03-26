/*
Basic ant follow behaviour, inherits behaviour.
Checks for two ants within eachothers radii.
The second ant then follows the first.
*/

#ifndef BEHAVIOURFOLLOW_H
#define BEHAVIOURFOLLOW_H

#include <string>
#include <ant.h>
#include <Behaviour.h>
#include <CollisionsManager.h>
class BehaviourFollow : public Behaviour
{
	public:
		BehaviourFollow();

		bool antInRadius(Ant &passedAnt1, Ant &passedAnt2, CollisionsManager &passedColMan);

		void followAnt(Ant &passedAnt1, Ant &passedAnt2,CollisionsManager &passedColMan);
		virtual void run();
		virtual void run(Ant &passedAnt1, Ant &passedAnt2, CollisionsManager &passedColMan);

	protected:

	private:
		

};

#endif