#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ant.h>


using namespace std;

int main()
{

	sf::RenderWindow Game(sf::VideoMode(800,600,32), "ALIEN ANT FARM");
	int i = 0; //value for switch statement, 0 - 5 represent different states, to be tidied up x

	Ant ant1(Ant(sf::Vector2f(100, 100), sf::Vector2f(20, 50), sf::Color::Red)), //controlled character
		ant2(Ant(sf::Vector2f(50, 50), sf::Vector2f(20, 50), sf::Color::Blue)),	// leaf npc
		hill(Ant(sf::Vector2f(500, 500), sf::Vector2f(100, 100), sf::Color::Green)); //ant hill

	while(Game.isOpen()) //game loop
	{
		sf::Event event;

		switch(Game.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				Game.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			ant1.rect.move(0, -0.1f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			ant1.rect.move(0, 0.1f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			ant1.rect.move(-0.1f, 0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			ant1.rect.move(0.1f, 0);
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

		// ^ Q and E reset states to 1 and 2 for vague debugging reasons, needed to make sure switch worked

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

		ant1.Update();
		ant2.Update();
		hill.Update();

		Game.clear(sf::Color::Black);
		Game.draw(ant1.rect);
		Game.draw(ant2.rect);
		Game.draw(hill.rect);
		Game.display();

	}

	return EXIT_SUCCESS;
}

//Ryan Wilson 23/02/15 ant-icipation