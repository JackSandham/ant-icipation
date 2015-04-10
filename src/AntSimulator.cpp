#include "AntSimulator.h"


AntSimulator::AntSimulator()
{
	// Instantiate singleton resource managers. These should not be deconstructed for the lifetime of the program
	m_pFontManager = FontManager::getInstance();
	m_pAudioManager = AudioManager::getInstance();
	m_pTextureManager = TextureManager::getInstance();
	m_pStringsManager = StringsManager::getInstance();

	// Configure Alarms (AKA Timers)
	AlarmList* al = AlarmList::getAlarmList();
	al->setCheckFrequency(60);
	al->addAlarmListener(this);
	al->addAlarm(Alarm("food_spawner", 5000, true));
	al->addAlarm(Alarm("ant_spawner", 3000, true));

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

	//set pointers to NULL at start
	m_RandomHillStartPos = nullptr;
}

void AntSimulator::buildUI()
{
	UIBuilder b(m_uiManager);
	b.buildUI("user_interfaces/main_constructor.txt", this);
	m_uiManager.setUILoaded(UIManager::UIs::MAIN, true);

	m_uiManager.getUIComponentRef("imgCheckboxCollectFood")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxFollow")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxSteer")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxAvoid")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxSeek")->addComponentListener(this);
	m_uiManager.getUIComponentRef("imgCheckboxFlee")->addComponentListener(this);
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
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x	

	//Gethins Adjacency Matrix
	MatrixController matrixControl; //--Gethin Changes
	//Declaring an AdjacencyMatrix in the main code

	m_pAnthill = new AntHill(Vector2D(400, 400), 100, 100);

	m_vAntEaterSpawn = new Vector2D(600,600);
	//m_vectorOfAntEaters.push_back(AntEater(*m_vAntEaterSpawn, 100, 100, sf::Color::Magenta));

	AntEater* antEater1 = new AntEater(*m_vAntEaterSpawn, 30, 70);
	m_antEaters.push_back(*antEater1);

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
		}

		//Movement for AntEater. Uses generic SFML bindings.
		//Problems - calling moveVisualObjects doesn't work repeatedly. I can use setPosition on the vector to move the anteater
		//but not the moveVisualObjects. Anyone able to chime in? I'm sure the code I've gotten is fine, but I'm just missing something.
		//as a result the radii aren't moving nor is the AABB
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
			{
				m_AntEaterit->setPosition(Vector2D(m_AntEaterit->getPosition().getX(), m_AntEaterit->getPosition().getY() - 0.7));
				m_AntEaterit->moveVisualObjects(m_AntEaterit->getPosition().getX(), m_AntEaterit->getPosition().getY());
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
			{
				m_AntEaterit->setPosition(Vector2D(m_AntEaterit->getPosition().getX(),m_AntEaterit->getPosition().getY() + 0.7));
				m_AntEaterit->moveVisualObjects(m_AntEaterit->getPosition().getX(),m_AntEaterit->getPosition().getY());		
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
			{
				m_AntEaterit->setPosition(Vector2D(m_AntEaterit->getPosition().getX() - 0.7 ,m_AntEaterit->getPosition().getY()));
				m_AntEaterit->moveVisualObjects(m_AntEaterit->getPosition().getX(),m_AntEaterit->getPosition().getY());		
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{			
			for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
			{
				m_AntEaterit->setPosition(Vector2D(m_AntEaterit->getPosition().getX() + 0.7,m_AntEaterit->getPosition().getY()));
				m_AntEaterit->moveVisualObjects(m_AntEaterit->getPosition().getX(),m_AntEaterit->getPosition().getY());		
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			m_window.close();
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

		UIText* txt = dynamic_cast<UIText*>(m_uiManager.getUIComponentRef("txtAnts"));
		txt->setString("Numbers of ants: " + std::to_string(m_ants.size()));

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
				if(m_CollisionsManager->AABBtoCircleCollision(**it,*m_antEaters.at(0).getAntEaterOuterRadius()))
				{
					m_antEaters.at(0).setColliding(true);
				}
				else if (iObsCounter == obstacles.size())
				{
					m_antEaters.at(0).setColliding(false);
				}
	
				//If avoiding behaviour is on
				if(isAvoiding)
				{
					antAvoid->run(*m_Antit,**it,*m_CollisionsManager);
				}

				//If fleeing behaviour is on
				if(isFleeing)
				{
					//If the ant is moving towards eater then we can only push.
					if(!m_antEaters.at(0).isColliding())
					{
						//Ant is not colliding with a obstacle
						if(!m_Antit->isColliding())
						{
							antFlee->run(*m_Antit, m_antEaters.at(0),*m_CollisionsManager);
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
				
				//if seek on
				if(isSeeking)
				{
					for (Food food : m_food)
					{
						// this is the gather food behaviour. it has alot of statements that might not make much sense but il try to explain as best as possible
						if(food.getCollidable()==true)//if the food can be collided
						{
							if(m_CollisionsManager->CircletoCircleCollision(*food.getFoodRadius(), *m_Antit->getAntRadius()) == true && food.getHome()==false)//if the ant and food radius collide and																																	//if the ant is not at the ant hill
							{
								antGather->run(*m_Antit, food, *m_CollisionsManager);//the ant will move towards the food itseld
							}

						}
						if((m_CollisionsManager->AABBtoAABBCollision(*m_Antit, food)==true) &&(food.getCollidable()==true)&& food.getHome()==false)//if the ant and food collide and the food is collidable																															//and the food is not at the ant hill
						{
							food.setCollidable(false);//set the food to no longer be collidable
							food.setCollected(true);//make it so the food has been collected
							m_Antit->setNumber(food.getFoodNumber());
							m_Antit->setFood(true);//the ant is now carrying food
						}

						if(food.getCollected()==true && food.getCollidable()==false && m_Antit->getFood()==true && m_Antit->getNumber()==food.getFoodNumber())//if the food has been collected and its not colllidable																					  //and the ant has food
						{
							food.setPosition(m_Antit->getPosition());//set the foods position to the ant
							antGather->goHome(*m_Antit, food, *m_CollisionsManager, *m_pAnthill);//make the ant start going to the ant hill
						}

						if((m_CollisionsManager->AABBtoAABBCollision(*m_Antit, *m_pAnthill)==true) && (food.getHome()==false) && (food.getCollected()==true)&& m_Antit->getNumber()==food.getFoodNumber())//if the ant and the and hill collide																															//and the food is collected
						{
							food.setPosition(m_pAnthill->getPosition());//set the foods position to be at the ant hill
							antSteer->randomDirection(*m_Antit);//choose a random direction for the ant to move
							m_Antit->setFood(false);//ant no longer has food
							food.setHome(true);//set it so the food is at the ant hill
							food.setCollidable(true);//the the food to be collidable again (this just stops it from going into other loops, it cant actually collide)
							iNumFood++;
						}
					}
				}
			}			
		}
				
		if(iNumFood == 4)
		{
			cout<<"Game Over"<<endl;
			//Disable movement 
			isAvoiding = false;
			isFleeing = false;
			isFollowing = false;
			isSeeking = false;
			isSteering = false;
		}

		//Move Multiple Ants
		for (m_Antit = m_ants.begin(); m_Antit != m_ants.end(); ++m_Antit)
		{
			m_Antit->Update(m_antEaters.at(0),*m_CollisionsManager);
			if (m_Antit->isMoveable())
			{
				m_Antit->setMovable(false);
				antSteer->randomDirection(*m_Antit);
			}
			matrixControl.setAntPosInMatrix(&*m_Antit, arrayMatrix);//--Gethin Changes
			//Put the function into the AdjacencyMatrix class and am calling it from there rather than it being a global function
		}

		for (m_AntEaterit = m_antEaters.begin(); m_AntEaterit != m_antEaters.end(); ++m_AntEaterit)
		{
			m_AntEaterit->Update();
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

	// Draw the ant hill
	m_window.draw(*m_pAnthill);

	// Draw all food
	for (std::vector<Food>::iterator it = m_food.begin(); it != m_food.end(); ++it)
	{
		m_window.draw(*it);
	}

	// Draw all ant-eaters
	for (std::vector<AntEater>::iterator it = m_antEaters.begin(); it != m_antEaters.end(); ++it)
	{
		m_window.draw(*it);
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
		m_bWillSpawnFood = true;
	}
	else if (e->getName() == "ant_spawner")
	{
		m_bWillSpawnAnt = true;
	}
}

void AntSimulator::spawnFood(double xPos, double yPos)
{
	Food f(Vector2D(xPos, yPos), 20, 20);
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
	if (sComponentName == "imgCheckboxCollectFood")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		isSeeking = !isSeeking;
		if (isSeeking)
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
		isFollowing = !isFollowing;
		if (isFollowing)
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
		isSteering = !isSteering;
		if (isSteering)
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
		isAvoiding = !isAvoiding;
		if (isAvoiding)
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
		isSeeking = !isSeeking;
		if (isSeeking)
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgCheckboxFlee")
	{
		UIComponent* u = m_uiManager.getUIComponentRef(sComponentName);
		UIImage* i = dynamic_cast<UIImage*>(u);
		isFleeing = !isFleeing;
		if (isFleeing)
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