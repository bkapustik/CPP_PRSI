#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Card.h"
#include "memory"
#include "iostream"
#include "ColorSprite.h"
#include "Button.h"

using namespace std;
using namespace sf;

class Opener
{
private:
	const string texturesRoot = "Textures";
	const string backgroundRoot = "Background";
	const string cardRoot = "Cards";
	const string cardBackSideRoot = "CardBackSite";
	const string menuRoot = "Menu";
	const string colorRoot = "Colors";
	Font font;
	string rootPath;

	string buildPath(vector<string> pathParts);
	string buildCardPath(const string color, const string number);
	CardFunctionNumber nameToNumber(const string& name);
	CardFunctionColor nameToColor(const string& color);
	unique_ptr<sf::Texture> getCardTexture(const string& path);

public:
	Opener();
	void operator=(const Opener& opener);
	unique_ptr<Texture> getMenuTexture(string startImage);
	string getBackgroundPath();
	vector<shared_ptr<Card>> getCards();
	sf::Texture getBackgroundTexture();

	static string colorToName(const CardFunctionColor& color);
	static string numberToName(const CardFunctionNumber& color);

	shared_ptr<Texture> getCardBackSide();
	vector<shared_ptr<ColorSprite>> getColorSprites(float screenWidth, float screenHeight);

	Button getButton(string text, float width, float height, float positionX, float positionY);
};

