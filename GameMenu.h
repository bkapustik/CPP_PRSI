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
	vector<unique_ptr<Card>> cards;
	vector<shared_ptr<ColorSprite>> colorSprites;

	unique_ptr<Texture> startTexture;
	unique_ptr<Texture> restartTexture;
	
	shared_ptr<Clock> clock;
	Deck deck;
	GraphicsHelper graphics;
	shared_ptr<Texture> cardBackSide;
	shared_ptr<bool> isHumanChoosingColor;

	Text winText;
	Text loseText;

	Button beSkippedButton;
	Button takeCardsButton;
	
public:
	GameState gameState;
	GameManager gameManager;
	Sprite background;
	shared_ptr<RenderWindow> window;

	Menu(float screenWidth, float screenHeight, const shared_ptr<RenderWindow> window, float secondsToWaitBetweenEachRound,const shared_ptr<Clock> clock);
	
	void render();
	void tryReactToMenuEvent();
	void playOneTurn();
};
