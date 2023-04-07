#include "SFML/Graphics.hpp"
#include "GameMenu.h"

using namespace std;
using namespace sf;

int main()
{
	float secondsToWaitBetweenEachRound = 0.5;
	float screenWidth = 1920;
	float screenHeight = 1080;
	
	auto window = make_shared<RenderWindow>(VideoMode(VideoMode(screenWidth, screenHeight)), "Pr��");
	auto clock = make_shared<Clock>(Clock());

	Event event;

	Menu menu = Menu(screenWidth, screenHeight, window, secondsToWaitBetweenEachRound, clock);

	while (window->isOpen()) {

		while (window->pollEvent(event)) {

			if (event.type == Event::Closed)
			{

				window->close();
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (!menu.gameManager.userInputReceived)
				{
					menu.gameManager.playOneTurn();
					
					if (menu.gameManager.PlayerHasFinished)
					{
						menu.gameState = playerWon;
					}

					clock->restart();
				}
				menu.doAction();
			}
		}

		window->clear(Color::White);

		window->draw(menu.background);

		menu.render();

		window->display();
	}

	return 0;
}