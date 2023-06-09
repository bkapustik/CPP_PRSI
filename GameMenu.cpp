#include "GameMenu.h"

#include <iostream>

using namespace std;

Menu::Menu(float screenWidth, float screenHeight, float secondsToWaitBetweenEachRound)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->secondsToWaitBetweenEachRound = secondsToWaitBetweenEachRound;
	this->gameState = GameState::initial;
	cards = opener.getCards();
	cardBackSide = opener.getCardBackSide();


	menuData = GameMenuDto();
	menuData.graphics = GraphicsHelper(2, 2, screenWidth, screenHeight, (*cards[0]), opener.getCardBackSide());
	menuData.deck = Deck(cards, menuData.graphics);

	isHumanChoosingColor = false;
	colorSprites = opener.getColorSprites(screenWidth, screenHeight);

	this->gameManager = GameManager(4, menuData, colorSprites);

	backgroundTexture = opener.getBackgroundTexture();
	background = Sprite(backgroundTexture);

	startTexture = move(opener.getMenuTexture("start.png"));
	restartTexture = move(opener.getMenuTexture("restart.png"));

	menuButton = Sprite(*this->startTexture);
	menuButton.setPosition((screenWidth - this->startTexture->getSize().x) / 2, (screenHeight - this->startTexture->getSize().y) / 2);

	winText = menuData.graphics.getText("You Win!");
	winText.setFillColor(Color::Green);
	loseText = menuData.graphics.getText("You Lose!");

	winText.setPosition(screenWidth / 2 - winText.getGlobalBounds().width / 2, screenHeight / 2 - 200);
	loseText.setPosition(screenWidth / 2 - loseText.getGlobalBounds().width / 2, screenHeight / 2 - 200);

	float buttonWidth = 200;
	float buttonHeight = 100;

	takeCardsButton = opener.getButton("Take Cards", buttonWidth, buttonHeight, screenWidth / 2 - 200, screenHeight / 2);
	beSkippedButton = opener.getButton("Be Skipped", buttonWidth, buttonHeight, screenWidth / 2 - 200, screenHeight / 2);
}

void Menu::playOneTurn()
{
	gameManager.playOneTurn(menuData, isHumanChoosingColor);
}

void Menu::displayGame(Clock & clock, RenderWindow & window)
{
	if (clock.getElapsedTime() > seconds(secondsToWaitBetweenEachRound) && gameManager.userInputReceived)
	{
		if (gameManager.PlayerHasFinished)
		{
			gameState = GameState::playerWon;
		}
		else 
		{
			gameManager.playOneTurn(menuData, isHumanChoosingColor);
			if (gameManager.Players.size() <= 1)
			{
				gameState = GameState::playerLost;
			}
		}
		clock.restart();
	}

	window.draw((*menuData.deck.frontDeckCard->sprite));

	for (auto& sprite : menuData.deck.sprites)
	{
		window.draw((*sprite));
	}

	for (auto player : gameManager.Players)
	{
		for (auto& card : player->cards)
		{
			window.draw((*card.sprite));
		}
	}

	if (gameManager.playerEvent == beingSkipped)
	{
		window.draw((*beSkippedButton.sprite));
		window.draw((*beSkippedButton.text));
	}

	if (gameManager.playerEvent == hasToTakeACard)
	{
		window.draw((*takeCardsButton.sprite));
		window.draw((*takeCardsButton.text));
	}
}

void Menu::displayColorOptions(RenderWindow & window)
{
	for (auto colorOption : gameManager.colorSprites)
	{
		window.draw((*colorOption->sprite));
	}
}

void Menu::tryReactToMenuEvent()
{
	if (gameState == GameState::initial || gameState == GameState::playerLost || gameState == GameState::playerWon)
	{
		if (Click::isClicked(menuButton))
		{
			cards = opener.getCards();
			menuData.deck = Deck(cards, menuData.graphics);
			this->gameManager = GameManager(4, menuData, colorSprites);
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
			gameManager.humanTakeCards(menuData);
		}
	}
}

void Menu::render(Clock & clock, RenderWindow & window)
{
	if (isHumanChoosingColor)
	{
		displayColorOptions(window);
	}
	else if (gameState == GameState::playing)
	{
		displayGame(clock, window);
	}
	else
	{
		displayMenu(window);
	}
}

void Menu::displayMenu(RenderWindow & window)
{
	window.draw(menuButton);
	if (gameState == GameState::playerWon)
	{
		window.draw(winText);
	}

	if (gameState == GameState::playerLost)
	{
		window.draw(loseText);
	}
}