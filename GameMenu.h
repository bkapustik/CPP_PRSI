#pragma once

#include "SFML/Graphics.hpp"
#include "Opener.h"
#include "Click.h"
#include "GameManager.h"
#include "GameStateData.h"

enum class GameState
{
	initial, playing, playerWon, playerLost, paused
};

class Menu
{
private:
	void displayMenu(RenderWindow & window);
	void displayGame(Clock & clock, RenderWindow & window);
	void displayColorOptions(RenderWindow & window);

	float screenWidth;
	float screenHeight;
	float secondsToWaitBetweenEachRound;
	Opener opener = Opener();
	Texture backgroundTexture;
	Sprite menuButton;
	vector<unique_ptr<Card>> cards;
	vector<shared_ptr<ColorSprite>> colorSprites;

	unique_ptr<Texture> startTexture;
	unique_ptr<Texture> restartTexture;
	
	GameMenuDto menuData;
	shared_ptr<Texture> cardBackSide;
	bool isHumanChoosingColor;

	Text winText;
	Text loseText;

	Button beSkippedButton;
	Button takeCardsButton;
	
public:
	GameState gameState;
	GameManager gameManager;
	Sprite background;

	Menu(float screenWidth, float screenHeight, float secondsToWaitBetweenEachRound);
	
	void render(Clock & clock, RenderWindow & window);
	void tryReactToMenuEvent();
	void playOneTurn();
};
