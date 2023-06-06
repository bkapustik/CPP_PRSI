#include "SFML/Graphics.hpp"
#include "GameMenu.h"
#include "Tests.h"

using namespace std;
using namespace sf;

int main()
{
	vector<unique_ptr<TestBase>> tests = vector<unique_ptr<TestBase>>();
	tests.push_back(make_unique<DeckTests>());
	tests.push_back(make_unique<PlayerTests>());
	tests.push_back(make_unique<GameManagerTests>());

	for (int i = 0; i < tests.size(); ++i)
	{
		tests[i]->execute();
	}
	// float secondsToWaitBetweenEachRound = 0.5;
	// float screenWidth = 1920;
	// float screenHeight = 1080;
	
	// RenderWindow window(VideoMode(screenWidth, screenHeight), "Prsi");
	// auto clock = Clock();

	// Event event;

	// Menu menu = Menu(screenWidth, screenHeight, secondsToWaitBetweenEachRound);

	// while (window.isOpen()) {

	// 	while (window.pollEvent(event)) {

	// 		if (event.type == Event::Closed)
	// 		{
	// 			window.close();
	// 		}
	// 		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	// 		{
	// 			if (!menu.gameManager.userInputReceived)
	// 			{
	// 				menu.playOneTurn();

	// 				clock.restart();
	// 			}
	// 			menu.tryReactToMenuEvent();
	// 		}
	// 	}

	// 	window.clear(Color::White);

	// 	window.draw(menu.background);

	// 	menu.render(clock, window);

	// 	window.display();
	// }

	return 0;
}