#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Card.h"
#include "memory"
#include "iostream"

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
	string rootPath;

	string buildPath(vector<string> pathParts);
	string buildCardPath(const string color, const string number);
	CardFunctionNumber nameToNumber(const string& name);
	CardFunctionColor nameToColor(const string& color);
	unique_ptr<sf::Texture> getCardTexture(const string& path);

public:
	Opener();
	unique_ptr<Texture> getMenuTexture(string startImage);
	string getBackgroundPath();
	vector<shared_ptr<Card>> getCards();
	sf::Texture getBackgroundTexture();

	static string colorToName(const CardFunctionColor& color);
	static string numberToName(const CardFunctionNumber& color);
	
	shared_ptr<Texture> getCardBackSide();
};

