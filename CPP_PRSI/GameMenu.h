#pragma once

#include "SFML/Graphics.hpp"
#include "Opener.h"
#include "Click.h"
#include "GameManager.h"

enum GameState
{
	initial, playing, playerWon, playerLost, paused
};

class Menu
{
private:
	void tryRestart();
	void displayMenu();
	void displayGame();

	float screenWidth;
	float screenHeight;
	float secondsToWaitBetweenEachRound;
	Opener opener = Opener();
	Texture backgroundTexture;
	Sprite menuButton;
	vector<shared_ptr<Card>> cards;
	
	unique_ptr<Texture> startTexture;
	unique_ptr<Texture> restartTexture;
	
	shared_ptr<Clock> clock;
	shared_ptr<Deck> deck;
	shared_ptr<GraphicsHelper> graphics;
	shared_ptr<Texture> cardBackSide;
public:
	Menu(float width, float height, shared_ptr<RenderWindow> window, float secondsToWaitBetweenEachRound, shared_ptr<Clock> clock);
	void render();
	void doAction();
	GameState gameState;
	GameManager gameManager;
	Sprite background;
	shared_ptr<RenderWindow> window;
};
