#pragma once

#include "SFML/Graphics.hpp"
#include "Opener.h"
#include "Click.h"
#include "GameManager.h"

enum class GameState
{
	initial, playing, playerWon, playerLost, paused
};

class Menu
{
private:
	void displayMenu();
	void displayGame();
	void displayColorOptions();

	float screenWidth;
	float screenHeight;
	float secondsToWaitBetweenEachRound;
	Opener opener = Opener();
	Texture backgroundTexture;
	Sprite menuButton;
	vector<shared_ptr<Card>> cards;
	vector<shared_ptr<ColorSprite>> colorSprites;

	unique_ptr<Texture> startTexture;
	unique_ptr<Texture> restartTexture;
	
	shared_ptr<Clock> clock;
	shared_ptr<Deck> deck;
	shared_ptr<GraphicsHelper> graphics;
	shared_ptr<Texture> cardBackSide;
	shared_ptr<bool> isHumanChoosingColor;

	Text winText;
	Text loseText;

	Button beSkippedButton;
	Button takeCardsButton;
	
public:
	Menu(float width, float height, shared_ptr<RenderWindow> window, float secondsToWaitBetweenEachRound, shared_ptr<Clock> clock);
	void render();
	void tryReactToMenuEvent();
	GameState gameState;
	GameManager gameManager;
	Sprite background;
	shared_ptr<RenderWindow> window;
};
