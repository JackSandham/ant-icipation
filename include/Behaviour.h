/**
This class is an abstract class that allows polymorphic calls to behaviour objects.

Also more importantly contains data nathan needs for his fancy user interface :D

@author Nathan
*/

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>

class Behaviour
{
	public:
		Behaviour(std::string sBehaviourName);

		bool isEnabled() const;

		virtual void enable();
		virtual void disable();

	protected:

	private:
		Behaviour();

		bool m_bIsEnabled;
		std::string m_sBehaviourName;
};

#endif