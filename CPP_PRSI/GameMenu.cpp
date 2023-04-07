#include "GameMenu.h"

Menu::Menu(float screenWidth, float screenHeight, shared_ptr<RenderWindow> window, float secondsToWaitBetweenEachRound, shared_ptr<Clock> clock)
{
	this->clock = clock;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->secondsToWaitBetweenEachRound = secondsToWaitBetweenEachRound;
	this->window = window;
	cards = opener.getCards();
	cardBackSide = opener.getCardBackSide();
	graphics = make_shared<GraphicsHelper>(2, 2, screenWidth, screenHeight, cards[0], opener.getCardBackSide());

	deck = make_shared<Deck>(Deck(cards, graphics));
	isHumanChoosingColor = make_shared<bool>(false);
	colorSprites = opener.getColorSprites(screenWidth, screenHeight);

	this->gameManager = GameManager(4, deck, graphics, isHumanChoosingColor, colorSprites);

	backgroundTexture = opener.getBackgroundTexture();
	background = Sprite(backgroundTexture);

	startTexture = move(opener.getMenuTexture("start.png"));
	restartTexture = move(opener.getMenuTexture("restart.png"));

	menuButton = Sprite(*this->startTexture);
	menuButton.setPosition((screenWidth - this->startTexture->getSize().x) / 2, (screenHeight - this->startTexture->getSize().y) / 2);
}

void Menu::displayGame()
{
	if (clock->getElapsedTime() > seconds(secondsToWaitBetweenEachRound) && gameManager.userInputReceived)
	{
		gameManager.playOneTurn();
		if (gameManager.Players.size() <= 1)
		{
			gameState = playerLost;
		}
		clock->restart();
	}

	window->draw((*deck->frontDeckCard));

	for (auto sprite : deck->sprites)
	{
		window->draw((*sprite));
	}

	for (auto player : gameManager.Players)
	{
		for (auto card : player->cards)
		{
			window->draw((*card.sprite));
		}
	}
}

void Menu::displayColorOptions()
{
	for (auto colorOption : gameManager.colorSprites)
	{
		window->draw((*colorOption->sprite));
	}
}

void Menu::tryRestart()
{
	if (gameState != playing)
	{
		if (Click::isClicked(menuButton))
		{
			deck = make_shared<Deck>(Deck(cards, graphics));
			this->gameManager = GameManager(4, deck, graphics, isHumanChoosingColor, colorSprites);
			gameState = playing;
			menuButton = Sprite(*this->restartTexture);
			menuButton.setPosition((screenWidth - this->startTexture->getSize().x) / 2, (screenHeight - this->startTexture->getSize().y) / 2);
		}
	}
}

void Menu::render()
{
	if ((*this->isHumanChoosingColor))
	{
		displayColorOptions();
	}
	else if (gameState == playing)
	{
		displayGame();
	}
	else
	{
		displayMenu();
	}
}

void Menu::displayMenu()
{
	window->draw(menuButton);
}