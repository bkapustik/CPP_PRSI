#include "GameMenu.h"

#include <iostream>

using namespace std;

Menu::Menu(float screenWidth, float screenHeight, const shared_ptr<RenderWindow> window, float secondsToWaitBetweenEachRound,const shared_ptr<Clock> clock)
{
	this->clock = clock;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->secondsToWaitBetweenEachRound = secondsToWaitBetweenEachRound;
	this->window = window;
	this->gameState = GameState::initial;
	cards = opener.getCards();
	cardBackSide = opener.getCardBackSide();
	graphics = GraphicsHelper(2, 2, screenWidth, screenHeight, (*cards[0]), opener.getCardBackSide());

	deck = Deck(cards, graphics);
	isHumanChoosingColor = false;
	colorSprites = opener.getColorSprites(screenWidth, screenHeight);

	this->gameManager = GameManager(4, deck, graphics, colorSprites);

	backgroundTexture = opener.getBackgroundTexture();
	background = Sprite(backgroundTexture);

	startTexture = move(opener.getMenuTexture("start.png"));
	restartTexture = move(opener.getMenuTexture("restart.png"));

	menuButton = Sprite(*this->startTexture);
	menuButton.setPosition((screenWidth - this->startTexture->getSize().x) / 2, (screenHeight - this->startTexture->getSize().y) / 2);

	winText = graphics.getText("You Win!");
	winText.setFillColor(Color::Green);
	loseText = graphics.getText("You Lose!");

	winText.setPosition(screenWidth / 2 - winText.getGlobalBounds().width / 2, screenHeight / 2 - 200);
	loseText.setPosition(screenWidth / 2 - loseText.getGlobalBounds().width / 2, screenHeight / 2 - 200);

	float buttonWidth = 200;
	float buttonHeight = 100;

	takeCardsButton = opener.getButton("Take Cards", buttonWidth, buttonHeight, screenWidth / 2 - 200, screenHeight / 2);
	beSkippedButton = opener.getButton("Be Skipped", buttonWidth, buttonHeight, screenWidth / 2 - 200, screenHeight / 2);
}

void Menu::playOneTurn()
{
	gameManager.playOneTurn(graphics, deck, isHumanChoosingColor);
}

void Menu::displayGame()
{
	if (clock->getElapsedTime() > seconds(secondsToWaitBetweenEachRound) && gameManager.userInputReceived)
	{
		gameManager.playOneTurn(graphics, deck, isHumanChoosingColor);
		if (gameManager.Players.size() <= 1)
		{
			gameState = GameState::playerLost;
		}
		clock->restart();
	}

	window->draw((*deck.frontDeckCard->sprite));

	for (auto& sprite : deck.sprites)
	{
		window->draw((*sprite));
	}

	for (auto player : gameManager.Players)
	{
		for (auto& card : player->cards)
		{
			window->draw((*card.sprite));
		}
	}

	if (gameManager.playerEvent == beingSkipped)
	{
		window->draw((*beSkippedButton.sprite));
		window->draw((*beSkippedButton.text));
	}

	if (gameManager.playerEvent == hasToTakeACard)
	{
		window->draw((*takeCardsButton.sprite));
		window->draw((*takeCardsButton.text));
	}
}

void Menu::displayColorOptions()
{
	for (auto colorOption : gameManager.colorSprites)
	{
		window->draw((*colorOption->sprite));
	}
}

void Menu::tryReactToMenuEvent()
{
	if (gameState == GameState::initial || gameState == GameState::playerLost || gameState == GameState::playerWon)
	{
		if (Click::isClicked(menuButton))
		{
			cards = opener.getCards();
			deck = Deck(cards, graphics);
			this->gameManager = GameManager(4, deck, graphics, colorSprites);
			gameState = GameState::playing;
			menuButton = Sprite(*this->restartTexture);
			menuButton.setPosition((screenWidth - this->startTexture->getSize().x) / 2, (screenHeight - this->startTexture->getSize().y) / 2);
		}
	}

	if (gameManager.playerEvent == PlayerEvent::beingSkipped)
	{
		if (Click::isClicked((*beSkippedButton.sprite)))
		{
			gameManager.humanSkip();
		}
	}

	if (gameManager.playerEvent == PlayerEvent::hasToTakeACard)
	{
		if (Click::isClicked((*takeCardsButton.sprite)))
		{
			gameManager.humanTakeCards(graphics, deck);
		}
	}
}

void Menu::render()
{
	if (isHumanChoosingColor)
	{
		displayColorOptions();
	}
	else if (gameState == GameState::playing)
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
	if (gameState == GameState::playerWon)
	{
		window->draw(winText);
	}

	if (gameState == GameState::playerLost)
	{
		window->draw(loseText);
	}
}