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
#include "Wall.h"
#include "AntHill.h"
#include "Rock.h"
#include "AlarmList.h"
#include "AlarmListener.h"
#include "Alarm.h"

using namespace std;

class AntSimulator : public UIButtonListener, public AlarmListener, public UIComponentListener
{
	public:
		AntSimulator();

		void run();
		void render();
		void buildUI();
		void gameOver();
		void spawnFood(double xPos, double yPos);
		void spawnAnt(double xPos, double yPos);

		virtual void buttonDepressed(std::string sButtonName);
		virtual void buttonReleased(std::string sButtonName);
		virtual void alarmExpired(AlarmEvent* e);
		virtual void componentDepressed(std::string sComponentName);
		virtual void componentReleased(std::string sComponentName);
		virtual void componentHovered(std::string sComponentName);
		virtual void componentUnhovered(std::string sComponentName);

	protected:

	private:
		UIManager m_uiManager;
		sf::RenderWindow m_window;
		sf::Sprite m_background;
		Randomiser m_randomiser;

		FontManager* m_pFontManager;
		AudioManager* m_pAudioManager;
		TextureManager* m_pTextureManager;
		StringsManager* m_pStringsManager;
		AlarmList* m_pAlarmList;

		bool m_bWillSpawnAnt;
		bool m_bWillSpawnFood;
		bool m_bAnteaterAIEnabled;

		int m_iAntsEaten;
		int m_iFoodCollected;

		// Vectors containing all objects present in the game world
		std::vector<Ant> m_ants;
		std::vector<Wall*> m_walls;
		std::vector<Rock*> m_rocks;
		std::vector<AntEater*> m_antEaters;
		std::vector<Food*> m_food;
		AntHill* m_pAnthill;

		std::vector<Ant>::iterator m_Antit; //!< iterator for this vector
		std::vector<AntEater*>::iterator m_AntEaterit;

		std::vector<Food*>::iterator m_Foodit;

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
		
		bool m_bFleeEnabled;
		bool m_bSeekEnabled;
		bool m_bAvoidEnabled;
		bool m_bFollowEnabled;
		bool m_bWanderEnabled;
		bool m_bSteerEnabled;
		bool m_bMoveEnabled;

		int iFoodNumber;

		BehaviourFollow* antFollow;
		BehaviourAvoid* antAvoid;
		BehaviourSteer* antSteer;
		BehaviourGather* antGather;
		BehaviourFlee* antFlee;
		CollisionsManager* m_CollisionsManager;
};

#endif