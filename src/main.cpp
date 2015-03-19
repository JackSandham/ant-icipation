#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "Tiles.h"
#include "Background.h"
#include <ant.h>
#include "circle.h"
#include "AABB.h"
#include "OBB.h"
#include "Shape.h"
#include "CollisionsManager.h"
#include "Vector2D.h"

using namespace std;

void setAntPosInMatrix(Ant* ant, char (&charArray)[50][50], Vector2D &xyPos, bool &btemp){
	if(btemp == true){
		charArray[(int)xyPos.getX()][(int)xyPos.getY()] = '.';
		btemp = false;
	}
	float xPos = ant->getPosition().x;	
	float yPos = ant->getPosition().y;
	xPos = xPos/1000;
	yPos = yPos/1000;
	xPos = xPos * 50;
	yPos = yPos * 50;
	xPos = (int)xPos;
	yPos = (int)yPos;
	charArray[(int)xPos][(int)yPos] = 'a';
	xyPos = Vector2D(xPos,yPos);
	btemp = true;

	cout<<xPos<<" "<<yPos<<" "<<endl;
	cout<<charArray[(int)xPos][(int)yPos]<<" "<<charArray[(int)xyPos.getX()][(int)xyPos.getY()]<<endl;

	for(int i = 0; i < 50; i++){
		for(int j = 0; j < 50; j++){
			cout<<charArray[i][j];
		}
		cout<<endl;
	}
}

int main()
{
	sf::Clock clock;//clock for updating frames
	sf::RenderWindow Game(sf::VideoMode(1000,1000,32), "ALIEN ANT FARM");
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x

	Ant* hill = new Ant(sf::Vector2f(500, 500),100,100,sf::Color::Blue); //ant hill

	Ant* ant1 = new Ant(hill->getPosition(),18,18,sf::Color::Red); //controlled character
	Circle* antRadius = new Circle(ant1->getPosition(), 50,sf::Color::Green);// ant detection radius
	Ant* ant2 = new Ant(sf::Vector2f(50, 50), 20,50,sf::Color::Green);	// leaf npc

	//Tanveer's Shapes for testing collisions
	Circle* m_circle = new Circle(sf::Vector2f(50,50), 50); //top left circle
	Circle* m_circle2 = new Circle(sf::Vector2f(50,151), 50); //circle underneath other circle. chamge ypos to 150 for circle circle test
	AABB* m_AABB = new AABB(sf::Vector2f(126,50),50,50); //first rectangle to the left of the circle. change xpos to 125 for circle aabb test
	AABB* m_AABB2 = new AABB(sf::Vector2f(177,50),50,50); //rectangle to the right of the first rectangle. change xpos to 176 for aabb aabb test
	OBB* m_OBB = new OBB(sf::Vector2f(136,150),50,50,45); //rotated aabb next to bottom circle. xpos to 135 for obb circle text
	//Collision Manager for testing collisions
	CollisionsManager* m_CollisionsManager = new CollisionsManager();

	bool move=true;
	Background back;
	fstream grid;
	const static int gridX = 50; //51
	const static int gridY = 50; //49
	char arrayMatrix[gridX][gridY];
	Vector2D tempPos(0,0);
	bool tempBool = false;
	bool bMapLoaded = false;

	for(int i = 0; i < gridX; i++){
		for(int j = 0; j < gridY; j++){
			arrayMatrix[i][j] = 0;
		}
	}
	grid.open("../Maps/Map1.txt", ios_base::in);
	if(grid.is_open()){
			for(int i = 0; i < gridX; i++){
				for(int j = 0; j < gridY; j++){
					grid>>arrayMatrix[i][j];
				}
			}
		grid.close();
	}
	else{
		cout<<"error";
	}

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
		if(bMapLoaded == false){
			int k = 0;
			for(int i = 0; i < gridX; i++){
				for(int j = 0; j < gridY; j++){
					switch(arrayMatrix[i][j]){
					case '.':
						back.setColour(sf::Color::White,k); //Free Space
						break;
					case '1':
						back.setColour(sf::Color::Magenta,k); //Change to brown for walls
						break;
				}
					k++;
			}
			bMapLoaded = true;
			}
		}
		// ^ Q and E reset states to 1 and 2 for vague debugging reasons, needed to make sure switch worked
		if(fElapsedTime>0.017)
		{
			ant1->move();
			antRadius->move(ant1->getPosition()); //update detection radius to ant
			/*
			if (m_CollisionsManager->CircletoCircleCollision(*m_circle,*m_circle2) ==true)
			{
				std::cout<<"i collided"<<endl; //circle with circle collision test
			}

			if (m_CollisionsManager->OBBtoCircleCollision(*m_OBB,*m_circle2) ==true)
			{
				std::cout<<"i collided"<<endl; //obb to circle collision text
			}
			*/
			//if aabb within radius
			if (m_CollisionsManager->AABBtoCircleCollision(*m_AABB,*antRadius) ==true)
			{
				std::cout<<"i collided"<<endl; //aabb to circle collision text
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
		setAntPosInMatrix(ant1, arrayMatrix, tempPos, tempBool);

		ant1->WallCollision(*ant1);
		ant2->Update();
		hill->Update();

		Game.clear(sf::Color::Black);
		back.drawBackground(Game);
		Game.draw(*m_AABB->getRectangle());
		Game.draw(*m_AABB2->getRectangle());
		Game.draw(*ant2->getRectangle());
		Game.draw(*hill->getRectangle());
		//Game.draw(*antRadius);
		Game.draw(*ant1->getRectangle());
		
		Game.display();

	}

	return EXIT_SUCCESS;
}



//Ryan Wilson 23/02/15 ant-icipation