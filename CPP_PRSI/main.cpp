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

using namespace std;
using namespace sf;

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

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{

				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !gameManager.userInputReceived)
			{
				gameManager.playOneTurn();
			}
		}
		if (clock.getElapsedTime() > seconds(1))
		{
			gameManager.playOneTurn();
			clock.restart();
		}

		window.clear(sf::Color::White);

		window.draw(background);

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

		window.display();
	}

	return 0;
}