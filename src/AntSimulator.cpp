#include "AntSimulator.h"


AntSimulator::AntSimulator()
{
	// Instantiate singleton resource managers. These should not be deconstructed for the lifetime of the program
	m_pFontManager = FontManager::getInstance();
	m_pAudioManager = AudioManager::getInstance();
	m_pTextureManager = TextureManager::getInstance();
	m_pStringsManager = StringsManager::getInstance();

	// Configure Alarms (AKA Timers)
	m_pAlarmList = AlarmList::getAlarmList();
	m_pAlarmList->setCheckFrequency(60);
	m_pAlarmList->addAlarmListener(this);
	m_pAlarmList->addAlarm(Alarm("food_spawner", 5000, true));
	m_pAlarmList->addAlarm(Alarm("ant_spawner", 1000, true));

	// Load textures
	m_pTextureManager->setWorkingDirectory("textures/");
	m_pTextureManager->loadTexture("ant", "ant.png");
	m_pTextureManager->loadTexture("wall", "wall.png");
	m_pTextureManager->loadTexture("food", "food.png");
	m_pTextureManager->loadTexture("rock", "rock.png");
	m_pTextureManager->loadTexture("ant_eater", "ant_eater.png");
	m_pTextureManager->loadTexture("wall", "wall.png");
	m_pTextureManager->loadTexture("ant_hill", "ant_hill.png");
	m_pTextureManager->loadTexture("background", "background.png");
	m_pTextureManager->loadTexture("vision_radius", "vision_radius.png");

	// Configure background
	m_pTextureManager->getTexture("background")->setRepeated(true);
	m_background.setPosition(300, 100);
	m_background.setTextureRect(sf::IntRect(0, 0, 900, 700));	
	m_background.setTexture(*m_pTextureManager->getTexture("background"));

	isFollowing = true;
	isFleeing = true;
	isAvoiding = true;
    isSteering = true;
	isSeeking = true;

	m_bWillSpawnAnt = false;
	m_bWillSpawnFood = false;
	m_iAntsEaten = 0;
	m_iFoodCollected = 0;
	m_bAnteaterAIEnabled = true;

	m_bFleeEnabled = true;
	m_bSeekEnabled = true;
	m_bAvoidEnabled = true;
	m_bFollowEnabled = true;
	m_bWanderEnabled = true;
	m_bSteerEnabled = true;
	m_bMoveEnabled = true;
}

void AntSimulator::buildUI()
{
	UIBuilder b(m_uiManager);
	b.buildUI("user_interfaces/main_constructor.txt", this);
	m_uiManager.setUILoaded(UIManager::UIs::MAIN, true);

	m_uiManager.getUIComponentRef("imgCheckboxFlee")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxSeek")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxAvoid")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxFollow")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxWander")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxSteer")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxMove")->addComponentListener(this);
}

/** 
Do stuff. 
This function includes the game loop. */
void AntSimulator::run()
{
	// Initialise components
	m_window.create(sf::VideoMode(1200, 800, 32), "ALIEN ANT FARM");
	m_window.setFramerateLimit(60);
	
	antFollow = new BehaviourFollow();
	antAvoid = new BehaviourAvoid();
	antSteer = new BehaviourSteer();
	antGather = new BehaviourGather();
	antFlee = new BehaviourFlee();
	m_CollisionsManager = new CollisionsManager();

	// Construct and attach the user interface to the window.
	buildUI();

	// ==========================================================================================

	sf::Clock clock;
	int iNumFood = 0;
	iFoodNumber=0;
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x	

	//Gethins Adjacency Matrix
	MatrixController matrixControl; //--Gethin Changes
	//Declaring an AdjacencyMatrix in the main code

	m_pAnthill = new AntHill(Vector2D(400, 400), 100, 100);
	m_pAnthill->setPosition(Vector2D(400, 400));

	m_vAntEaterSpawn = new Vector2D(600,600);
	//m_vectorOfAntEaters.push_back(AntEater(*m_vAntEaterSpawn, 100, 100, sf::Color::Magenta));

	AntEater* antEater1 = new AntEater(*m_vAntEaterSpawn, 40, 80);
	m_antEaters.push_back(antEater1);

	Background back;
	char arrayMatrix[GRIDX][GRIDY]; //--Gethin Changes
	//Used the grid variable defined in the AdjacencyMatrix class to set the size of the grid.

	matrixControl.presetMatrix(arrayMatrix);//--Gethin Changes
	matrixControl.constructMatrix(arrayMatrix);//--Gethin Changes
	//Took the two functions that were here and put them inside the Adjacency Matrix class.

	back.assignMatrixValues(arrayMatrix, m_rocks, m_walls); //--Gethin Changes

	std::vector<AABB*> obstacles;
	std::vector<Wall*>::iterator wit;
	std::vector<Rock*>::iterator rit;
	for (wit = m_walls.begin(); wit != m_walls.end(); ++wit)
	{
		obstacles.push_back(*wit);
	}
	for (rit = m_rocks.begin(); rit != m_rocks.end(); ++rit)
	{
		obstacles.push_back(*rit);
	}

	// ==========================================================================================================
	// Game loop begins here
	while (m_window.isOpen())
	{
		// This will cap the "logic" rate at 60 ticks per second. The logic and frame rate will match, so no processing power
		// is wasted.
		if (clock.getElapsedTime().asMilliseconds() < 17)
		{
			continue;
		}

		// ==========================================================================================================
		// Start event checks
		
		sf::Event event;
		while (m_window.pollEvent(event))
		{	
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				m_uiManager.checkReleaseEvents(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				m_uiManager.checkDepressEvents(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					m_bAnteaterAIEnabled = !m_bAnteaterAIEnabled;
				}
			}
		}

		//Temp follow off switch
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			isFollowing = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			i = 2;
		}

		// End event checks
		// ==========================================================================================================
		// Start logical updates

		UIText* txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtAntsAlive"));
		txt->setString("Ants alive: " + std::to_string(m_ants.size()));
		txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtAntsEaten"));
		txt->setString("Ants eaten: " + std::to_string(m_iAntsEaten));
		txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtFoodAlive"));
		txt->setString("Food: " + std::to_string(m_food.size()));
		txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtFoodGathered"));
		txt->setString("Food gathered: " + std::to_string(m_iFoodCollected));
		txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtAnteaterHunger"));
		if (m_antEaters.at(0)->isHungry())
		{		
			txt->setString("Anteater status: Hungry");
		}
		else
		{
			txt->setString("Anteater status: Full");
		}

		if (m_bWillSpawnAnt)
		{
			m_bWillSpawnAnt = false;
			spawnAnt(400, 400);
		}
		if (m_bWillSpawnFood)
		{
			m_bWillSpawnFood = false;
			double x = m_randomiser.getRandom(100, 800);
			double y = m_randomiser.getRandom(100, 600);
			spawnFood(x, y);
		}

		//Move/collide Multiple Ants
		int iAntCounter = 0;
		int iObsCounter = 0;
		for (m_Antit = m_ants.begin(); m_Antit != m_ants.end(); ++m_Antit)
		{
			++iAntCounter;
			antSteer->move(*m_Antit);
			for (std::vector<AABB*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
			{
				++iObsCounter;
				//emergency if we collide with an obstacle.
				if(m_CollisionsManager->AABBtoAABBCollision(*m_Antit,**it))
				{
					m_Antit->setDirection(Vector2D(0,0));
					m_CollisionsManager->correctPosition(*m_Antit);
				}
				if(m_CollisionsManager->AABBtoCircleCollision(**it, *(m_antEaters.at(0))->getAntEaterOuterRadius()))
				{
					m_antEaters.at(0)->setColliding(true);
				}
				else if (iObsCounter == obstacles.size())
				{
					m_antEaters.at(0)->setColliding(false);
				}
	
				//If avoiding behaviour is on
				
				if(isAvoiding)
				{
					antAvoid->run(*m_Antit,**it,*m_CollisionsManager, *antSteer);
					if(isSteering && antSteer->isEnabled())
					{
						antSteer->run(*m_Antit);
						antSteer->disable();
					}
				}
				
				//If fleeing behaviour is on
				if(isFleeing)
				{
					//If the ant is moving towards eater then we can only push.
					if(!m_antEaters.at(0)->isColliding())
					{
						//Ant is not colliding with a obstacle
						if(!m_Antit->isColliding())
						{
							antFlee->run(*m_Antit, *m_antEaters.at(0),*m_CollisionsManager);
						}
					}
					
				}
			}
			//If we are not fleeing!
			if(!m_Antit->isFleeing())
			{
				//If there is no collision, then we can check for antfollow.
				//If following behaviour is on
				if(isFollowing)
				{
					if(!m_Antit->isColliding())
					{
						if (iAntCounter != m_ants.size())
						{
							antFollow->run(*m_Antit, m_ants.at(iAntCounter), *m_CollisionsManager);
						}
					}
				}
				/*
				If we are not following, then change direction on col.
				Will be changed with steer behaviour.
				I.E will default to steer behaviour if not following?
				*/
				
				// =======================================================================================================
				// "Seeking" behaviour. The seeking behaviour references the ability for ants 
				// to find, collect and deliver food to the ant hill.
				if(isSeeking)
				{
					if (m_Antit->isCarryingFood())
					{
						if (m_CollisionsManager->AABBtoAABBCollision(*m_Antit, *m_pAnthill))
						{
							Food* f = m_Antit->getFood();
							m_Antit->dropFood();
							m_iFoodCollected++;

							for (int i = 0; i < m_food.size(); ++i)
							{
								if (f == m_food.at(i))
								{
									m_food.erase(m_food.begin() + i);
								}
							}
						}

						m_Antit->moveTowards(m_pAnthill->getPosition());	
					}
					else
					{
						// Search for nearby food
						// When these values are 10000, they are equivalent to "no food found"
						float distanceToNearestFood = 10000;
						Vector2D targetPos(0, 0);
						Food* f;
						float temp = 10000;
						for (std::vector<Food*>::iterator it = m_food.begin(); it != m_food.end(); ++it)
						{
							if ((*it)->isCollidable())
							{
								temp = (*it)->distanceTo(m_Antit->getPosition());
								if (temp < distanceToNearestFood)
								{
									distanceToNearestFood = temp;
									targetPos = (*it)->getPosition();
									f = *it;
								}
							}
						}

						// If a piece of food was found, check whether we are close enough to pick it up
						if (distanceToNearestFood < m_Antit->getCollectionRange())
						{
							m_Antit->assignFood(f);
						}
						// If we couldnt pick it up, check if we are in range to "sense" it and move towards it.
						else if (distanceToNearestFood < m_Antit->getFoodDetectionRadius())
						{
							m_Antit->moveTowards(targetPos);
						}
						else
						{
							// No action is taken, the food was too far away.
						}
					}
				}

				// =======================================================================================================
			}			
		}

		//Move Multiple Ants
		for (m_Antit = m_ants.begin(); m_Antit != m_ants.end(); ++m_Antit)
		{
			m_Antit->update(*m_antEaters.at(0),*m_CollisionsManager);
			if (m_Antit->isMoveable())
			{
				m_Antit->setMovable(false);
				antSteer->randomDirection(*m_Antit);
			}
			matrixControl.setAntPosInMatrix(&*m_Antit, arrayMatrix);//--Gethin Changes
			//Put the function into the AdjacencyMatrix class and am calling it from there rather than it being a global function
		}

		// Check collision between the ants and the anteater. If an ant is caught, it is deleted.
		for (std::vector<AntEater*>::iterator it_eater = m_antEaters.begin(); it_eater != m_antEaters.end(); ++it_eater)
		{
			for (int i = 0; i < m_ants.size(); ++i)
			{
				if (m_CollisionsManager->AABBtoAABBCollision(m_ants.at(i), **it_eater))
				{
					if (m_ants.at(i).isCarryingFood())
					{
						m_ants.at(i).dropFood();
					}
					m_ants.erase(m_ants.begin() + i);
					i--;
					m_iAntsEaten++;
					(*it_eater)->antEaten();
				}
			}
		}

		// ==============================================================================================
		// Start anteater logic
		if (m_bAnteaterAIEnabled)
		{
			for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
			{
				(*m_AntEaterit)->update();

				// When these values are 10000, they are equivalent to "no ant found"
				float distanceToNearestAnt = 10000;
				Vector2D targetPos(0, 0);
				float temp = 10000;
				if ((*m_AntEaterit)->isHungry())
				{
					// Search for a nearby ant.
					for (std::vector<Ant>::iterator it = m_ants.begin(); it != m_ants.end(); ++it)
					{
						temp = (*m_AntEaterit)->distanceTo((*it).getPosition());
						if (temp < distanceToNearestAnt)
						{
							distanceToNearestAnt = temp;
							targetPos = (*it).getPosition();
						}
					}
				}

				// If there was an Ant, move towards it. Otherwise, continue wandering.
				if (distanceToNearestAnt < (*m_AntEaterit)->getDetectionRadius())
				{
					(*m_AntEaterit)->moveTowards(targetPos);
				}
				else
				{
					(*m_AntEaterit)->wander();
				}
			}
		}

		// End anteater logic
		// ==============================================================================================

		if(m_iAntsEaten >= 200)
		{
			system("pause");
			m_window.close();
		}

		render();

		clock.restart();
	}
}

/** 
Render the game. */
void AntSimulator::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);

	// Draw the walls
	for (std::vector<Wall*>::iterator it = m_walls.begin(); it != m_walls.end(); ++it)
	{
		m_window.draw(**it);
	}

	// Draw rocks
	for (std::vector<Rock*>::iterator it = m_rocks.begin(); it != m_rocks.end(); ++it)
	{
		m_window.draw(**it);
	}

	// Draw all ants
	for (std::vector<Ant>::iterator it = m_ants.begin(); it != m_ants.end(); ++it)
	{
		m_window.draw(*it);
	}

	// Draw all food
	for (std::vector<Food*>::iterator it = m_food.begin(); it != m_food.end(); ++it)
	{
		m_window.draw(**it);
	}
	// Draw the ant hill
	m_window.draw(*m_pAnthill);

	// Draw all ant-eaters
	for (std::vector<AntEater*>::iterator it = m_antEaters.begin(); it != m_antEaters.end(); ++it)
	{
		m_window.draw(**it);
	}

	// This line will draw the ENTIRE user interface.
	m_window.draw(m_uiManager.getRootComponent());
	m_window.display();
}

/** 
Respond to buttons being depressed on the user interface. */
void AntSimulator::buttonDepressed(std::string sButtonName)
{
	// Do nothing. Intentional.
}

/** 
Respond to buttons being released on the user interface. */
void AntSimulator::buttonReleased(std::string sButtonName)
{
	// Do nothing. Intentional.
}		

void AntSimulator::alarmExpired(AlarmEvent* e)
{
	if (e->getName() == "food_spawner")
	{
		// Maximum of 8 food to prevent lag and clutter
		if (m_food.size() <= 8)
		{
			m_bWillSpawnFood = true;
		}
	}
	else if (e->getName() == "ant_spawner")
	{
		// Maximum of 25 ants to prevent lag
		AlarmList* al = AlarmList::getAlarmList(); 
		long currentDuration = al->getAlarm("ant_spawner")->getDuration();
		al->getAlarm("ant_spawner")->extendDuration(m_randomiser.getRandom(-(currentDuration - 1000), 7000 - currentDuration));
		if (m_ants.size() <= 25)
		{
			m_bWillSpawnAnt = true;
		}
	}
}

void AntSimulator::spawnFood(double xPos, double yPos)
{
	Food* f = new Food(Vector2D(xPos, yPos), 20, 20);
	m_food.push_back(f);
}

void AntSimulator::spawnAnt(double xPos, double yPos)
{
	Ant a(Vector2D(xPos, yPos), 20, 20);
	a.setRadiusVisibility(false);
	m_ants.push_back(a);
}

void AntSimulator::gameOver()
{
	// Code end state here
}

void AntSimulator::componentDepressed(std::string sComponentName)
{
	// Do nothing. Intentional.
}

void AntSimulator::componentReleased(std::string sComponentName)
{
	if (sComponentName == "imgCheckboxFlee")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bFleeEnabled = !m_bFleeEnabled;
		if (m_bFleeEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxSeek")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bSeekEnabled = !m_bSeekEnabled;
		if (m_bSeekEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxAvoid")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bAvoidEnabled = !m_bAvoidEnabled;
		if (m_bAvoidEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxFollow")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bFollowEnabled = !m_bFollowEnabled;
		if (m_bFollowEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxWander")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bWanderEnabled = !m_bWanderEnabled;
		if (m_bWanderEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxSteer")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bSteerEnabled = !m_bSteerEnabled;
		if (m_bSteerEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxMove")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_bMoveEnabled = !m_bMoveEnabled;
		if (m_bMoveEnabled)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
}

void AntSimulator::componentHovered(std::string sComponentName)
{
	// Do nothing. Intentional.
}

void AntSimulator::componentUnhovered(std::string sComponentName)
{
	// Do nothing. Intentional.
}