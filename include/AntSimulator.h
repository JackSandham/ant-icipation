/*Gethin Changes
Anything that I have changed I have put //--Gethin Changes after and then put a description below it

I have also removed the Tiles class from the program as it is used at all so was pointless
(this was my class not sure why I added it though)
The tiles class that is in this project is the old GameTiles class. The Tiles class and GameTiles class need to be removed and then this Tiles class needs to be added.

I have created a brand new class AdjacencyMatrix and have modified the Background and GameTiles classes
*/


#ifndef ANT_SIMULATOR_H
#define ANT_SIMULATOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "Background.h"
#include <ant.h>
#include <antEater.h>
#include <Behaviour.h>
#include <BehaviourFollow.h>
#include <BehaviourAvoid.h>
#include "BehaviourSteer.h"
#include "BehaviourGather.h"
#include "BehaviourFlee.h"
#include "circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Shape.h"
#include "Food.h"
#include "CollisionsManager.h"
#include "Vector2D.h"
#include "MatrixController.h"
#include "Randomiser.h"
#include "FontManager.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "StringsManager.h"
#include "UIManager.h"
#include "UIBuilder.h"
#include "UIButtonListener.h"


using namespace std;

class AntSimulator : UIButtonListener
{
	public:
		AntSimulator();
		~AntSimulator();
		void run();
		void render();
		void buildUI();
		void GameOver();

		virtual void buttonDepressed(std::string sButtonName);
		virtual void buttonReleased(std::string sButtonName);

	protected:

	private:
		sf::RenderWindow m_window;
		UIManager m_uiManager;

		std::vector<Shape*> m_vectorOfShapes; //!< A pointer to shapes held in a vector

		std::vector<Ant> m_vectorOfAnts;
		std::vector<Ant>::iterator m_Antit; //!< iterator for this vector

		std::vector<AntEater> m_vectorOfAntEaters;
		std::vector<AntEater>::iterator m_AntEaterit;

		std::vector<AABB> m_vectorOfAABB; //!< Holds AABB objects
		std::vector<AABB>::iterator m_AABBit; //!< iterator for this vector

		std::vector<OBB> m_vectorOfOBB; //!< Holds OBB objects
		std::vector<OBB>::iterator m_OBBit; //!< iterator for this vector

		std::vector<Circle> m_vectorOfCircles; //!< Holds OBB objects
		std::vector<Circle>::iterator m_Circleit; //!< iterator for this vector

		std::vector<Food> m_vectorOfFood;
		std::vector<Food>::iterator m_Foodit;

		std::vector<Behaviour*> m_behaviours;

		Randomiser m_RandomStartPosX;
		float m_fRandomStartPosX;
		Randomiser m_RandomStartPosY;
		float m_fRandomStartPosY;
		Vector2D* m_RandomHillStartPos;
		Vector2D* m_vAntEaterSpawn;
		
		
		bool isFollowing;
		bool isFleeing;
		bool isAvoiding;
		bool isSteering;
		bool isSeeking;
		
		BehaviourFollow* antFollow;
		BehaviourAvoid* antAvoid;
		BehaviourSteer* antSteer;
		BehaviourGather* antGather;
		BehaviourFlee* antFlee;
		CollisionsManager* m_CollisionsManager;
};

#endif