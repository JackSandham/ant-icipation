#include "Behaviour.h"

/**
Default constructor. Don't call this. Ever. */
Behaviour::Behaviour()
{
	m_sBehaviourName = "ERROR";
}

/**
Constructs a behaviour object, setting the behaviour name in the process. Note that the name is really only
for debugging purposes.

@param sBehaviourName The name of the behaviour. */
Behaviour::Behaviour(std::string sBehaviourName)
{
	m_sBehaviourName = sBehaviourName;
}