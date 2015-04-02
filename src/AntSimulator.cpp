#include "AntSimulator.h"

AntSimulator::AntSimulator()
{
	// Instantiate singleton resource managers. These should not be deconstructed for the lifetime of the program.
	FontManager* m_pFontManager = FontManager::getInstance();
	AudioManager* m_pAudioManager = AudioManager::getInstance();
	TextureManager* m_pTextureManager = TextureManager::getInstance();
	StringsManager* m_pStringsManager = StringsManager::getInstance();

	isFollowing = true;
	isAvoiding = true;
    isSteering = true;
	isSeeking = false;
	//set pointers to NULL at start
	m_RandomHillStartPos = NULL;
}
AntSimulator::~AntSimulator()
{
	if(m_RandomHillStartPos != NULL)
	{
		delete m_RandomHillStartPos;
	}
	m_RandomHillStartPos = NULL;

	if(antFollow != NULL)
	{
		delete antFollow;
	}
	antFollow = NULL;

	if(antAvoid != NULL)
	{
		delete antAvoid;
	}
	antAvoid = NULL;

	if(antSteer != NULL){
		delete antSteer;
	}
	antSteer = NULL;

	if(antGather != NULL)
	{
		delete antGather;
	}
	antGather = NULL;

	if(m_CollisionsManager != NULL)
	{
		delete m_CollisionsManager;
	}

	m_CollisionsManager = NULL;
}
void AntSimulator::buildUI()
{
	UIBuilder b(m_uiManager);
	b.buildUI("user_interfaces/main_constructor.txt", this);
	m_uiManager.setUILoaded(UIManager::UIs::MAIN, true);
}

/** 
Do stuff. 
This function includes the game loop. */
void AntSimulator::run()
{
	m_window.create(sf::VideoMode(1000, 1000, 32), "ALIEN ANT FARM");
	m_window.setFramerateLimit(60);
	sf::Clock clock;//clock for updating frames
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x

	//Gethins Adjacency Matrix
	MatrixController matrixControl; //--Gethin Changes
	//Declaring an AdjacencyMatrix in the main code

	AABB* hill = new Ant(Vector2D(500, 500), 100, 100, sf::Color::Green); //ant hill (spawn)
	m_vectorOfAABB.push_back(*hill);
	//antz
	for(int x = 0;x<5;++x)
	{
		m_fRandomStartPosX = m_RandomStartPosX.getRandom(hill->getMin().getX(),hill->getMax().getX());
		m_fRandomStartPosY = m_RandomStartPosY.getRandom(hill->getMin().getY(),hill->getMax().getY());
		m_RandomHillStartPos = new Vector2D(m_fRandomStartPosX,m_fRandomStartPosY);
		m_vectorOfAnts.push_back(Ant(*m_RandomHillStartPos, 18, 18, sf::Color::Red));
		m_vectorOfAnts.at(x).setRadiusVisibility(false);
	}
	//anteater basic draw
	Ant* antEater = new Ant(Vector2D(800,800), 100, 100, sf::Color::Magenta);
	m_vectorOfAnts.push_back(*antEater);
	
	antFollow = new BehaviourFollow();
	antAvoid = new BehaviourAvoid();
	antSteer = new BehaviourSteer();
	antGather = new BehaviourGather();
	//Tanveer's Shapes for testing collisions
	//m_vectorOfCircles.push_back(Circle(sf::Vector2f(50,50), 50,sf::Color::Magenta)); //top left circle
	//m_vectorOfCircles.push_back(Circle(sf::Vector2f(50,151), 50,sf::Color::Green)); //circle underneath other circle. chamge ypos to 150 for circle circle test
	//m_vectorOfAABB.push_back(AABB(sf::Vector2f(126,50),50,50)); //first rectangle to the left of the circle. change xpos to 125 for circle aabb test
	//m_vectorOfAABB.push_back(AABB(sf::Vector2f(177,50),50,50)); //rectangle to the right of the first rectangle. change xpos to 176 for aabb aabb test
	//m_vectorOfOBB.push_back(OBB(sf::Vector2f(136,150),50,50,45)); //rotated aabb next to bottom circle. xpos to 135 for obb circle text


	//Collision Manager for testing collisions
	m_CollisionsManager = new CollisionsManager();

	Background back;
	char arrayMatrix[GRIDX][GRIDY]; //--Gethin Changes
	//Used the grid variable defined in the AdjacencyMatrix class to set the size of the grid.

	matrixControl.presetMatrix(arrayMatrix);//--Gethin Changes
	matrixControl.constructMatrix(arrayMatrix);//--Gethin Changes
	//Took the two functions that were here and put them inside the Adjacency Matrix class.


	/*
	Add all vectors to vector of shapes for drawing
	*/
	for (m_Antit = m_vectorOfAnts.begin(); m_Antit != m_vectorOfAnts.end(); ++m_Antit)
	{
		//m_vectorOfShapes.push_back(&*m_Antit);
	}
	for (m_Circleit = m_vectorOfCircles.begin(); m_Circleit != m_vectorOfCircles.end(); ++m_Circleit)
	{
		m_vectorOfShapes.push_back(&*m_Circleit);
	}
	for (m_AABBit = m_vectorOfAABB.begin(); m_AABBit != m_vectorOfAABB.end(); ++m_AABBit)
	{
		m_vectorOfShapes.push_back(&*m_AABBit);
	}
	for (m_OBBit = m_vectorOfOBB.begin(); m_OBBit != m_vectorOfOBB.end(); ++m_OBBit)
	{
		m_vectorOfShapes.push_back(&*m_OBBit);
	}

	back.assignMatrixValues(arrayMatrix); //--Gethin Changes
	//I removed the statement that was here and put it into the Background class and am calling it from there as well.



	/*
	Had to move all of this out of the game loop because every frame, more shapes were getting added to the vector
	so the program was getting very laggy. now they are just added once and the program runs much smoother.
	*/  // - Tanveer

	std::vector<AABB*> obstacles = back.getObstacles();
	std::vector<AABB*>::iterator obstaclesit;

	std::vector<Food*> m_vectorOfFood = back.getFood();
	std::vector<Food*>::iterator Foodit;

	for (obstaclesit = obstacles.begin(); obstaclesit != obstacles.end(); ++obstaclesit)
	{
		m_vectorOfShapes.push_back(&**obstaclesit);// adds all the shapes in the adjacency matrix to the shapes vector
	}

	for (Foodit = m_vectorOfFood.begin(); Foodit != m_vectorOfFood.end(); ++Foodit)
	{
		m_vectorOfShapes.push_back(&**Foodit);// adds all the shapes in the adjacency matrix to the shapes vector
	}

	while (m_window.isOpen()) //game loop
	{
		sf::Event event;
		//find out elapsed time
		float fElapsedTime = clock.getElapsedTime().asSeconds();
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//ant1->setPosition(Vector2D(ant1->getPosition().getX(), ant1->getPosition().getY() - 0.1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//ant1->setPosition(Vector2D(ant1->getPosition().getX(), ant1->getPosition().getY() + 0.1));

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//ant1->setPosition(Vector2D(ant1->getPosition().getX() - 0.1, ant1->getPosition().getY()));

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//ant1->setPosition(Vector2D(ant1->getPosition().getX() + 0.1, ant1->getPosition().getY()));

		}

		// ^ movement controls for testing, unless people want I'm not going to try to implement AI movement until we have an adjancency matrix implemented

		//Temp follow off switch
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//i = 1;
			
			
			isFollowing = false;
		
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			i = 2;
		}

		// ^ Q and E reset states to 1 and 2 for vague debugging reasons, needed to make sure switch worked
		if (fElapsedTime>0.01)
		{
			//Move/collide Multiple Ants
			int iAntCounter = 0;

			for (m_Antit = m_vectorOfAnts.begin(); m_Antit != m_vectorOfAnts.end(); ++m_Antit)
			{
				++iAntCounter;
				antSteer->move(*m_Antit);


				/*
				Collision tests now iterate over vectors.
				*/

				//if Circle within radius
				for (auto Circle : m_vectorOfCircles)
				{
					if (m_CollisionsManager->CircletoCircleCollision(Circle, *m_Antit->getAntRadius()) == true)
					{
						//std::cout << "i collided" << endl; //aabb to circle collision text
					}
				}



				//if OBB within radius
				for (auto OBB : m_vectorOfOBB)
				{
					if (m_CollisionsManager->OBBtoCircleCollision(OBB, *m_Antit->getAntRadius()) == true)
					{
						std::cout << "i collided" << endl; //obb to circle collision text

					}
				}

			

				//if aabb within radius
				for (auto AABB : m_vectorOfAABB)
				{
					if (m_CollisionsManager->AABBtoCircleCollision(AABB, *m_Antit->getAntRadius()) == true)
					{
						//std::cout << "i collided" << endl; //aabb to circle collision text
					}
				}
				/*

				Run ant behaviours through obstacles!

				*/
				for (obstaclesit = obstacles.begin(); obstaclesit != obstacles.end(); ++obstaclesit)
				{
					
					antAvoid->run(*m_Antit,**obstaclesit,*m_CollisionsManager);
					//If there is no collision, then we can check for antfollow.
					if(isFollowing)
					{
						if(!antAvoid->isColliding() & !isSeeking)
						{

							if (iAntCounter != m_vectorOfAnts.size())
							{
								antFollow->run(*m_Antit, m_vectorOfAnts.at(iAntCounter), *m_CollisionsManager);
							}
						}
					}
					/*
					If we are not following, then change direction on col.
					Will be changed with steer behaviour.
					I.E will default to steer behaviour if not following?
					*/
					else
					{
						if(antAvoid->isColliding())
						{
							antSteer->randomDirection(*m_Antit);
						}
					}
				}
				for (auto Food : m_vectorOfFood)
				{
					// this is the gather food behaviour. it has alot of statements that might not make much sense but il try to explain as best as possible
					
					if(Food->getCollidable()==true)//if the food can be collided
					{
						if(m_CollisionsManager->CircletoCircleCollision(*Food->getFoodRadius(), *m_Antit->getAntRadius()) == true && Food->getHome()==false)//if the ant and food radius collide and
																																							//if the ant is not at the ant hill
						{
							antGather->run(*m_Antit,*Food,*m_CollisionsManager);//the ant will move towards the food itseld
						}
						
					}
					
					if((m_CollisionsManager->AABBtoAABBCollision(*m_Antit,*Food)==true) &&(Food->getCollidable()==true)&& Food->getHome()==false)//if the ant and food collide and the food is collidable
																																				//and the food is not at the ant hill
					{
						Food->setCollidable(false);//set the food to no longer be collidable
						Food->setCollected(true);//make it so the food has been collected
						m_Antit->setFood(true);//the ant is now carrying food
					}

					if(Food->getCollected()==true && Food->getCollidable()==false && m_Antit->getFood()==true)//if the food has been collected and its not colllidable
																											  //and the ant has food
					{
						Food->setPosition(m_Antit->getPosition());//set the foods position to the ant
						antGather->goHome(*m_Antit,*Food,*m_CollisionsManager,*hill);//make the ant start going to the ant hill
					}

					if((m_CollisionsManager->AABBtoAABBCollision(*m_Antit,*hill)==true) &&(Food->getHome()==false) && (Food->getCollected()==true))//if the ant and the and hill collide
																																					//and the food is not at the ant hill
																																					//and the food is collected
					{
						Food->setPosition(hill->getPosition());//set the foods position to be at the ant hill
						antSteer->randomDirection(*m_Antit);//choose a random direction for the ant to move
						m_Antit->setFood(false);//ant no longer has food
						Food->setHome(true);//set it so the food is at the ant hill
						Food->setCollidable(true);//the the food to be collidable again (this just stops it from going into other loops, it cant actually collide)
					}

				}

			}


			clock.restart(); //restart the clock to update frames	
		}
		/*
		if(ant1.Collision(ant2)) //for time being, used 'ant2' to represent a leaf
		{
		ant1.rect.setFillColor(sf::Color::Magenta); //this runs on the first loop round and changes i to 3... can't figure out why, probably simple fix
		i = 3;
		}
		else if(ant1.Collision(hill)) // big green anthill
		{
		ant1.rect.setFillColor(sf::Color::Green);
		i = 1;
		}
		else
		{
		ant1.rect.setFillColor(sf::Color::Red); // visual indicator of collision
		}
		
		
		switch(i) // state change statement
		{
		case 0:
			//cout << "0"<< endl; break;// state 0 exists for a reason I think 
		case 1:
			//cout << "1"<< endl; break;//change game state to seek. incl avoid - I can't see a reason to seperate avoid from everything else. Perhaps if I implement avoid as "0" but that triggers alongside everything else? 
										// either way seek becomes default, using value rather than switch default
		case 2:
			//cout << "2"<< endl; break;// change game state to follow - i = 2 if ant1.Collision(ant2followRadius), I'll leave that to tanveer
		case 3:
			//cout << "3"<< endl; break;//change game state to return - i = 3 if ant1.Collision(leaf) wee fella will return to the ant hill
		case 4:
			//cout << "4" << endl; break;//change game state to flee - i = 4 if ant1.Collision(antEaterRadius). Still unsure of how this will play out until the adjacency matrix is running. 
										// can probably do something like making the ant move slightly faster than the anteaterso it escapes its field of view.
		case 5:
			//cout << "3 and 4" <<endl; break; //change game state to fleeing and returning. Depending on how "dynamic" fleeing might be this may be redundant as switch statements
											//can cover multiple cases with one variable... something to mull over
		default:
			//cout << "Default"; //default game state, probably seek as well, it's just there in case anything breaks 
		}
		*/
		//Move Multiple Ants
		for (m_Antit = m_vectorOfAnts.begin(); m_Antit != m_vectorOfAnts.end(); ++m_Antit)
		{
			m_Antit->Update();
			if (m_Antit->isMoveable())
			{
				m_Antit->setMovable(false);
				antSteer->randomDirection(*m_Antit);
			}
			matrixControl.setAntPosInMatrix(&*m_Antit, arrayMatrix);//--Gethin Changes
			//Put the function into the AdjacencyMatrix class and am calling it from there rather than it being a global function

		}

		render();
	}
}

/** 
Render the game. */
void AntSimulator::render()
{
	m_window.clear(sf::Color::Black);
	//back.drawBackground(Game); //disabled this because it makes it extremely laggy

	//draw all shapes
	for (auto shape : m_vectorOfShapes)
	{
		m_window.draw(*shape);
	}
	for (m_Antit = m_vectorOfAnts.begin(); m_Antit != m_vectorOfAnts.end(); ++m_Antit)
	{
		m_window.draw(*m_Antit);//seperate for the moment.
	}



	// This line will draw the ENTIRE user interface.
	m_window.draw(m_uiManager.getRootComponent());
	m_window.display();
}

/** 
Respond to buttons being depressed on the user interface. */
void AntSimulator::buttonDepressed(std::string sButtonName)
{
	// Do nothing on depress. It looks weird.
}

/** 
Respond to buttons being released on the user interface. */
void AntSimulator::buttonReleased(std::string sButtonName)
{
	if (sButtonName == "behaviour_follow")
	{
		
	}
	else if (sButtonName == "behaviour_seek")
	{

	}
	else if (sButtonName == "behaviour_flee")
	{

	}
	else if (sButtonName == "behaviour_move")
	{

	}
}