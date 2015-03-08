/**
This class is an abstract class that allows polymorphic calls to behaviour objects.

All implementations of an ants behaviour should inherit this class, and all actions to be executed
should occur from a call to the 'run' function.

Usage example: A behaviour subclass is called BehaviourMoveForward. The subclass implements the run function so
that every game loop iteration the ant moves forward 3 pixels. 

Note that as this behaviour baseclass is abstract, references to it may only be stored as pointers. A std::vector
of pointers to behaviour objects will be satisfactory in almost all cases.

@author Nathan
*/

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>

class Behaviour
{
	public:
		Behaviour(std::string sBehaviourName);

		virtual void run() = 0;

	protected:
	private:
		Behaviour();

		std::string m_sBehaviourName;
};

#endif