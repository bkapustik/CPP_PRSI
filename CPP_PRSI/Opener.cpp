#include "Opener.h"


string Opener::buildPath(vector<string> pathParts)
{
	string path = ".";
	for (auto i = 0; i < pathParts.size(); ++i)
	{
		path += '/' + pathParts[i];
	}
	return path;
}

string Opener::buildCardPath(const string color, const string number)
{
	return rootPath + '/' + color + '/' + number + ".jpg";
}

CardFunctionNumber Opener::nameToNumber(const string& name)
{
	if (name == "seven")
	{
		return CardFunctionNumber::seven;
	}
	if (name == "eight")
	{
		return CardFunctionNumber::eight;
	}
	if (name == "nine")
	{
		return CardFunctionNumber::nine;
	}
	if (name == "ten")
	{
		return CardFunctionNumber::ten;
	}
	if (name == "bot")
	{
		return CardFunctionNumber::bot;
	}
	if (name == "top")
	{
		return CardFunctionNumber::top;
	}
	if (name == "king")
	{
		return CardFunctionNumber::king;
	}
	else
		return CardFunctionNumber::ace;
}

CardFunctionColor Opener::nameToColor(const string& color)
{
	if (color == "Acorns")
	{
		return CardFunctionColor::acorn;
	}
	if (color == "Balls")
	{
		return CardFunctionColor::bell;
	}
	if (color == "Green")
	{
		return CardFunctionColor::leaf;
	}
	else
		return CardFunctionColor::heart;
}

unique_ptr<sf::Texture> Opener::getCardTexture(const string& path)
{
	auto texture = make_unique<sf::Texture>(Texture());
	texture->loadFromFile(path);
	return texture;
}

Opener::Opener()
{
	rootPath = buildPath(vector<string>{ texturesRoot, cardRoot });
}

void Opener::operator=(const Opener& opener)
{
	*this = opener;
}

string Opener::getBackgroundPath()
{
	const string backgroundImage = "2796727.jpg";
	auto pathParts = vector<string>{ texturesRoot, backgroundRoot, backgroundImage };
	return buildPath(pathParts);
}

vector<shared_ptr<Card>> Opener::getCards()
{
	vector<string> cardNames = vector<string>({ "seven","eight","nine","ten","bot","top","king","ace" });
	vector<string> cardColors = vector<string>({ "Acorns","Balls","Green","Heart" });

	vector<shared_ptr<Card>> cards = vector<shared_ptr<Card>>();

	for (auto color : cardColors)
	{
		for (auto name : cardNames)
		{
			string path = buildCardPath(color, name);

			auto texture = move(getCardTexture(path));
			auto functionColor = nameToColor(color);
			auto functionNumber = nameToNumber(name);

			auto card = make_shared<Card>(Card(functionNumber, functionColor, move(texture)));
			cards.push_back(card);
		}
	}

	return cards;
}

shared_ptr<Texture> Opener::getCardBackSide()
{
	const string backSideImage = "back.jpg";
	auto pathParts = vector<string>{ texturesRoot, cardBackSideRoot, backSideImage };
	string path = buildPath(pathParts);
	auto texture = make_unique<Texture>(Texture());
	texture->loadFromFile(path);
	return texture;
}

vector<shared_ptr<ColorSprite>> Opener::getColorSprites(float screenWidth, float screenHeight)
{
	vector<string> colors = vector<string>({ "Acorns","Balls","Green","Heart" });
	vector<shared_ptr<ColorSprite>> cardColors = vector<shared_ptr<ColorSprite>>();

	for (auto color : colors)
	{
		string path = buildPath(vector<string>{ texturesRoot, colorRoot, color + ".jpg" });

		auto texture = make_unique<Texture>(Texture());
		texture->loadFromFile(path);

		auto cardColor = make_shared<ColorSprite>(nameToColor(color), move(texture));
		cardColors.push_back(cardColor);
	}

	int colorOptionWidth = 200;
	int colorOptionHeight = colorOptionWidth * 2;

	int spaceBetweenColorOptions = 50;

	float xPositionRelativeToCenter = -(colorOptionWidth * 2 + spaceBetweenColorOptions * 1.5);

	for (int i = 0; i < cardColors.size(); i++)
	{
		cardColors[i]->sprite->setTextureRect(IntRect(Vector2i(0, 0), Vector2i(colorOptionWidth, colorOptionHeight)));

		cardColors[i]->sprite->setPosition((screenWidth / 2) + xPositionRelativeToCenter, (screenHeight - colorOptionHeight) / 2);
	
		xPositionRelativeToCenter += colorOptionWidth + spaceBetweenColorOptions;
	}

	return cardColors;
}

unique_ptr<Texture> Opener::getMenuTexture(string startImage)
{
	auto pathParts = vector<string>{ texturesRoot, menuRoot, startImage };
	unique_ptr<Texture> texture = make_unique<Texture>(Texture());
	string path = buildPath(pathParts);
	texture->loadFromFile(path);
	return texture;
}

sf::Texture Opener::getBackgroundTexture()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(getBackgroundPath());
	return backgroundTexture;
}

string Opener::colorToName(const CardFunctionColor& color)
{
	switch (color)
	{
	case CardFunctionColor::leaf:
		return "leaf";
	case CardFunctionColor::heart:
		return "heart";
	case CardFunctionColor::acorn:
		return "acorn";
	case CardFunctionColor::bell:
		return "bell";
	}
}
string Opener::numberToName(const CardFunctionNumber& number)
{
	switch (number)
	{
	case CardFunctionNumber::seven:
		return "seven";
	case CardFunctionNumber::eight:
		return "eight";
	case CardFunctionNumber::nine:
		return "nine";
	case CardFunctionNumber::ten:
		return "ten";
	case CardFunctionNumber::bot:
		return "bot";
	case CardFunctionNumber::top:
		return "top";
	case CardFunctionNumber::king:
		return "king";
	case CardFunctionNumber::ace:
		return "ace";
	}
}

