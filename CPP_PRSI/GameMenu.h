#pragma once

#include "SFML/Graphics.hpp"
#include "Opener.h"

enum GameState
{
	initial, playing, playerWon, playerLost
};

class Menu
{
public:
	GameState gameState;
	unique_ptr<Texture> startTexture;
	unique_ptr<Texture> restartTexture;

	Sprite menuButton;
	Menu(float width, float height, unique_ptr<Texture> startTexture, unique_ptr<Texture> restartTexture);
	bool isSpriteClicked();
};
