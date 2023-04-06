#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <queue>
#include "CardFunctionColor.h"
#include "CardFunctionNumber.h"
#include "Card.h"
#include "Opener.h"
#include "Deck.h"
#include "GameManager.h"
#include "GraphicsHelper.h"
#include "GameMenu.h"

using namespace std;
using namespace sf;

float secondsToWaitBetweenEachRound = 0.5;

void displayGame(shared_ptr<Deck> deck, RenderWindow& window, GameManager& gameManager, Clock& clock)
{
	if (clock.getElapsedTime() > seconds(secondsToWaitBetweenEachRound) && gameManager.userInputReceived)
	{
		gameManager.playOneTurn();
		clock.restart();
	}

	window.draw((*deck->frontDeckCard));

	for (auto sprite : deck->sprites)
	{
		window.draw((*sprite));
	}

	for (auto player : gameManager.Players)
	{
		for (auto card : player->cards)
		{
			window.draw((*card.sprite));
		}
	}

	//if (gameManager.)
}

void displayMenu(RenderWindow& window, Menu& menu)
{
	window.draw(menu.menuButton);
}

void render(shared_ptr<Deck> deck, RenderWindow& window, GameManager& gameManager, Clock& clock, Menu& menu)
{
	if (menu.gameState == playing)
	{
		displayGame(deck, window, gameManager, clock);
	}
	else
	{
		displayMenu(window, menu);
	}
}

int main()
{
	Opener opener = Opener();
	auto cards = opener.getCards();
	float screenWidth = 1920;
	float screenHeight = 1080;
	auto cardBackSide = opener.getCardBackSide();
	auto graphics = make_shared<GraphicsHelper>(2, 2, screenWidth, screenHeight, cards[0], opener.getCardBackSide());

	auto deck = make_shared<Deck>(Deck(cards, graphics));
	GameManager gameManager(4, deck, graphics);

	sf::RenderWindow window(sf::VideoMode(VideoMode(screenWidth, screenHeight)), "Prší");
	sf::Texture backgroundTexture = opener.getBackgroundTexture();
	sf::Sprite background(backgroundTexture);
	sf::Event event;
	Clock clock;
	Menu menu = Menu(screenWidth, screenHeight, move(opener.getMenuTexture("start.png")), move(opener.getMenuTexture("restart.png")));

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{

				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (!gameManager.userInputReceived)
				{
					gameManager.playOneTurn();
					clock.restart();
				}
				if (menu.gameState != playing)
				{
					if (menu.isSpriteClicked())
					{
						menu.gameState = playing;
					}
				}
			}
		}

		window.clear(sf::Color::White);

		window.draw(background);

		render(deck, window, gameManager, clock, menu);

		window.display();
	}

	return 0;
}