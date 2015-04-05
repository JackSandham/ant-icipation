/*
Basic ant flee behaviour, inherits behaviour.
When an anteater is in radius, flee.
*/

#ifndef BEHAVIOURFLEE_H
#define BEHAVIOURFLEE_H

#include <string>
#include <ant.h>
#include <Behaviour.h>
#include <Background.h>
#include <CollisionsManager.h>
#include "BehaviourSteer.h"
#include "antEater.h"

class BehaviourFlee : public Behaviour
{
	public:
		BehaviourFlee();

		bool antEaterInRadius(Ant &passedAnt1, Eater &passedAntEater, CollisionsManager &passedColMan);
		bool isColliding();

		void avoidEater(Ant &passedAnt1, Eater &passedAntEater,CollisionsManager &passedColMan);
		virtual void run(Ant &passedAnt1, Eater &passedAntEater, CollisionsManager &passedColMan);

	protected:

	private:
		BehaviourSteer steerBehaviour;
		bool m_bAntColliding;

};

#endif