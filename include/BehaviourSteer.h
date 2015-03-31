/**
A class used for the ants behaviour "Steer".

This class includes the code for the ant to steer.

@author Gethin
*/

#ifndef BEHAVIOURSTEER_H
#define BEHAVIOURSTEER_H

#include "Randomiser.h"
#include <string>
#include "ant.h"
#include <ant.h>
#include <Behaviour.h>
#include <CollisionsManager.h>

class BehaviourSteer : public Behaviour {
public:
	BehaviourSteer(); //This is the default constructor for the BehaviourSteer class
	void randomDirection(Ant &passedAnt1); //This function is used to give the ant a random direction. This function was taken from the ant class.
	void move(Ant &passedAnt1); //This function is used to move the ant. This function was taken from the ant class.
	void moveup(Ant &passedAnt1); //This function is used to move the ant up. This function was taken from the ant class.
	void movedown(Ant &passedAnt1); //This function is used to move the ant down. This function was taken from the ant class.
	void moveleft(Ant &passedAnt1); //This function is used to move the ant left. This function was taken from the ant class.
	void moveright(Ant &passedAnt1); //This function is used to move the ant right. This function was taken from the ant class.
	void WallCollision(Ant &passedAnt1); //This function is used when the ant collides with a wall. This function was taken from the ant class.

	void update(Ant &passedAnt1);
private:
	Randomiser m_randomiser; //This is a random object used to create a random number.
	Vector2D m_vDirection; //This Vector2D is used to store the direction of the Ant.
};

#endif