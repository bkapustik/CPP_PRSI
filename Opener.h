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

	string buildPath(const vector<string> & pathParts) const;
	string buildCardPath(const string & color, const string & number) const;
	CardFunctionNumber nameToNumber(const string& name) const;
	CardFunctionColor nameToColor(const string& color) const;
	unique_ptr<sf::Texture> getCardTexture(const string& path) const;

public:
	Opener();
	void operator=(const Opener& opener);
	unique_ptr<Texture> getMenuTexture(string startImage) const;
	string getBackgroundPath() const;
	vector<unique_ptr<Card>> getCards() const;
	sf::Texture getBackgroundTexture() const;

	static string colorToName(const CardFunctionColor& color);
	static string numberToName(const CardFunctionNumber& color);

	shared_ptr<Texture> getCardBackSide() const;
	vector<shared_ptr<ColorSprite>> getColorSprites(float screenWidth, float screenHeight) const;

	Button getButton(const string & text, float width, float height, float positionX, float positionY) const;
};

