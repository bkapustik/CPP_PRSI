#include "SFML/Graphics.hpp"
#include "GameMenu.h"

using namespace std;
using namespace sf;

int main()
{
	float secondsToWaitBetweenEachRound = 0.5;
	float screenWidth = 1920;
	float screenHeight = 1080;
	
	auto window = make_shared<RenderWindow>(VideoMode(VideoMode(screenWidth, screenHeight)), "Prsi");
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
					menu.playOneTurn();

					clock->restart();
				}
				menu.tryReactToMenuEvent();
			}
		}

		window->clear(Color::White);

		window->draw(menu.background);

		menu.render();

		window->display();
	}

	return 0;
}