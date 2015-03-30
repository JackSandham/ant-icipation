/*
Basic ant avoid behaviour, inherits behaviour.
When an obstacle is in radius, avoid.
*/

#ifndef BEHAVIOURAVOID_H
#define BEHAVIOURAVOID_H

#include <string>
#include <ant.h>
#include <Behaviour.h>
#include <Background.h>
#include <CollisionsManager.h>
#include "BehaviourSteer.h"

class BehaviourAvoid : public Behaviour
{
	public:
		BehaviourAvoid();

		bool obstacleInRadius(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan);
		bool isColliding();

		void avoidObstacle(Ant &passedAnt1, AABB &passedBackObstacles,CollisionsManager &passedColMan);
		virtual void run(Ant &passedAnt1, AABB &passedBackObstacles, CollisionsManager &passedColMan);

	protected:

	private:
		BehaviourSteer steerBehaviour;
		bool m_bAntColliding;

};

#endif