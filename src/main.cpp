#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "Background.h"
#include <ant.h>
#include "circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Shape.h"
#include "CollisionsManager.h"
#include "Vector2D.h"
#include "MatrixController.h"

/*Gethin Changes
Anything that I have changed I have put //--Gethin Changes after and then put a description below it

I have also removed the Tiles class from the program as it is used at all so was pointless 
(this was my class not sure why I added it though)
The tiles class that is in this project is the old GameTiles class. The Tiles class and GameTiles class need to be removed and then this Tiles class needs to be added.

I have created a brand new class AdjacencyMatrix and have modified the Background and GameTiles classes
*/
using namespace std;

int main()
{
	sf::Clock clock;//clock for updating frames
	sf::RenderWindow Game(sf::VideoMode(1000,1000,32), "ALIEN ANT FARM");
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x

	//Gethins Adjacency Matrix
	MatrixController matrixControl; //--Gethin Changes
	//Declaring an AdjacencyMatrix in the main code

	/*
	Vectors to hold all shapes. 
	Shapes are all drawn from vector of shapes. Apart from ants for the moment.
	Allows for iterating over multiple shapes for collision tests.
	*/
	std::vector<Shape*> m_vectorOfShapes; //!< A pointer to shapes held in a vector

	std::vector<Ant> m_vectorOfAnts;
	std::vector<Ant>::iterator m_Antit; //!< iterator for this vector

	std::vector<AABB> m_vectorOfAABB; //!< Holds AABB objects
	std::vector<AABB>::iterator m_AABBit; //!< iterator for this vector

	std::vector<OBB> m_vectorOfOBB; //!< Holds OBB objects
	std::vector<OBB>::iterator m_OBBit; //!< iterator for this vector

	std::vector<Circle> m_vectorOfCircles; //!< Holds OBB objects
	std::vector<Circle>::iterator m_Circleit; //!< iterator for this vector

	AABB* hill = new Ant(sf::Vector2f(500, 500),100,100,sf::Color::Blue); //ant hill

	Ant* ant1 = new Ant(hill->getPosition(),18,18,sf::Color::Red); //controlled character
	m_vectorOfAnts.push_back(*ant1);
	Ant* ant2 = new Ant(sf::Vector2f(50, 50), 20,50,sf::Color::Green);	// leaf npc
	m_vectorOfAnts.push_back(*ant2);

	//Tanveer's Shapes for testing collisions
	m_vectorOfCircles.push_back(Circle(sf::Vector2f(50,50), 50,sf::Color::Magenta)); //top left circle
	m_vectorOfCircles.push_back(Circle(sf::Vector2f(50,151), 50,sf::Color::Green)); //circle underneath other circle. chamge ypos to 150 for circle circle test
	m_vectorOfAABB.push_back(AABB(sf::Vector2f(126,50),50,50)); //first rectangle to the left of the circle. change xpos to 125 for circle aabb test
	m_vectorOfAABB.push_back(AABB(sf::Vector2f(177,50),50,50)); //rectangle to the right of the first rectangle. change xpos to 176 for aabb aabb test
	m_vectorOfOBB.push_back(OBB(sf::Vector2f(136,150),50,50,45)); //rotated aabb next to bottom circle. xpos to 135 for obb circle text
	
	
	//Collision Manager for testing collisions
	CollisionsManager* m_CollisionsManager = new CollisionsManager();

	bool move=true;
	Background back;
	char arrayMatrix[GRIDX][GRIDY]; //--Gethin Changes
	//Used the grid variable defined in the AdjacencyMatrix class to set the size of the grid.

	matrixControl.presetMatrix(arrayMatrix);//--Gethin Changes
	matrixControl.constructMatrix(arrayMatrix);//--Gethin Changes
	//Took the two functions that were here and put them inside the Adjacency Matrix class.

	while(Game.isOpen()) //game loop
	{
		sf::Event event;
		//find out elapsed time
		float fElapsedTime = clock.getElapsedTime().asSeconds();
		while(Game.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				Game.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			ant1->setPosition(sf::Vector2f(ant1->getPosition().x,ant1->getPosition().y-0.1));	
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			ant1->setPosition(sf::Vector2f(ant1->getPosition().x,ant1->getPosition().y+0.1));
			
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			ant1->setPosition(sf::Vector2f(ant1->getPosition().x-0.1,ant1->getPosition().y));
			
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			ant1->setPosition(sf::Vector2f(ant1->getPosition().x+0.1,ant1->getPosition().y));
			
		}

		// ^ movement controls for testing, unless people want I'm not going to try to implement AI movement until we have an adjancency matrix implemented

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			i = 1;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			i = 2;
		}

		back.assignMatrixValues(arrayMatrix); //--Gethin Changes
		//I removed the statement that was here and put it into the Background class and am calling it from there as well.
		
		// ^ Q and E reset states to 1 and 2 for vague debugging reasons, needed to make sure switch worked
		if(fElapsedTime>0.017)
		{
			ant1->move();
			
			/*
			Collision tests now iterate over vectors.
			*/
			
			//if Circle within radius
			for(auto Circle : m_vectorOfCircles)
			{
				if (m_CollisionsManager->CircletoCircleCollision(Circle,*ant1->getAntRadius()) ==true)
				{
				std::cout<<"i collided"<<endl; //aabb to circle collision text
				}
			}
			//if OBB within radius
			for(auto OBB : m_vectorOfOBB)
			{
				if (m_CollisionsManager->OBBtoCircleCollision(OBB,*ant1->getAntRadius()) ==true)
				{
					std::cout<<"i collided"<<endl; //obb to circle collision text
				}
			}
			
			//if aabb within radius
			for(auto AABB : m_vectorOfAABB)
			{
				if (m_CollisionsManager->AABBtoCircleCollision(AABB,*ant1->getAntRadius()) ==true)
				{
				std::cout<<"i collided"<<endl; //aabb to circle collision text
				}
			}
			
			/*
			if (m_CollisionsManager->AABBtoAABBCollision(*m_AABB,*m_AABB2) ==true)
			{
				std::cout<<"i collided"<<endl; //aabb to aabb collision test
			}
			
			if (m_CollisionsManager->AABBtoAABBCollision(*ant1,*m_AABB2) == true)
			{
				std::cout<<"i collided"<<endl; //aabb to aabb collision test
			}
			*/
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
		*/
		switch(i) // state change statement
		{
		case 0:
			cout << "0"<< endl; break;// state 0 exists for a reason I think 
		case 1:
			cout << "1"<< endl; break;//change game state to seek. incl avoid - I can't see a reason to seperate avoid from everything else. Perhaps if I implement avoid as "0" but that triggers alongside everything else? 
										// either way seek becomes default, using value rather than switch default
		case 2:
			cout << "2"<< endl; break;// change game state to follow - i = 2 if ant1.Collision(ant2followRadius), I'll leave that to tanveer
		case 3:
			cout << "3"<< endl; break;//change game state to return - i = 3 if ant1.Collision(leaf) wee fella will return to the ant hill
		case 4:
			cout << "4" << endl; break;//change game state to flee - i = 4 if ant1.Collision(antEaterRadius). Still unsure of how this will play out until the adjacency matrix is running. 
										// can probably do something like making the ant move slightly faster than the anteaterso it escapes its field of view.
		case 5:
			cout << "3 and 4" <<endl; break; //change game state to fleeing and returning. Depending on how "dynamic" fleeing might be this may be redundant as switch statements
											//can cover multiple cases with one variable... something to mull over
		default:
			cout << "Default"; //default game state, probably seek as well, it's just there in case anything breaks 
		}

		ant1->Update();
		if(move==true)
		{
			move=false;
			ant1->randomMovement();
		}
		matrixControl.setAntPosInMatrix(ant1, arrayMatrix);//--Gethin Changes
		//Put the function into the AdjacencyMatrix class and am calling it from there rather than it being a global function

		ant1->WallCollision(*ant1);
		ant2->Update();
		//hill->Update();

		/*
		Add all vectors to vector of shapes for drawing
		*/
		for(m_Antit=m_vectorOfAnts.begin();m_Antit!=m_vectorOfAnts.end();++m_Antit)
		{
			//m_vectorOfShapes.push_back(&*m_Antit);
		}
		for(m_Circleit=m_vectorOfCircles.begin();m_Circleit!=m_vectorOfCircles.end();++m_Circleit)
		{
			m_vectorOfShapes.push_back(&*m_Circleit);
		}
		for(m_AABBit=m_vectorOfAABB.begin();m_AABBit!=m_vectorOfAABB.end();++m_AABBit)
		{
			m_vectorOfShapes.push_back(&*m_AABBit);
		}
		for(m_OBBit=m_vectorOfOBB.begin();m_OBBit!=m_vectorOfOBB.end();++m_OBBit)
		{
			m_vectorOfShapes.push_back(&*m_OBBit);
		}

		Game.clear(sf::Color::Black);
		back.drawBackground(Game);
		/*
		Game.draw(*m_AABB->getRectangle());
		Game.draw(*m_AABB2->getRectangle());
		Game.draw(*ant2->getRectangle());
		Game.draw(*hill->getRectangle());
		Game.draw(*antRadius);
		*/
		Game.draw(*ant1);//seperate for the moment.
		
		//draw all shapes
		for(auto shape : m_vectorOfShapes)
		{
			Game.draw(*shape);
		}

		Game.display();

	}

	return EXIT_SUCCESS;
}

