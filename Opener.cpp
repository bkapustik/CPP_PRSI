#include "Opener.h"

string Opener::buildPath(const vector<string> & pathParts) const
{
	string path = "..";
	for (auto i = 0; i < pathParts.size(); ++i)
	{
		path += '/' + pathParts[i];
	}
	return path;
}

string Opener::buildCardPath(const string & color, const string & number) const
{
	return rootPath + '/' + color + '/' + number + ".jpg";
}

CardFunctionNumber Opener::nameToNumber(const string& name) const
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

CardFunctionColor Opener::nameToColor(const string& color) const
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

unique_ptr<sf::Texture> Opener::getCardTexture(const string& path) const
{
	auto texture = make_unique<sf::Texture>(Texture());
	texture->loadFromFile(path);
	return texture;
}

Opener::Opener()
{
	rootPath = buildPath(vector<string>{ texturesRoot, cardRoot });
	font = Font();
	font.loadFromFile("../Fonts/videotype.otf");
}

void Opener::operator=(const Opener& opener)
{
	*this = opener;
}

string Opener::getBackgroundPath() const
{
	const string backgroundImage = "2796727.jpg";
	auto pathParts = vector<string>{ texturesRoot, backgroundRoot, backgroundImage };
	return buildPath(pathParts);
}

vector<unique_ptr<Card>> Opener::getCards() const
{
	vector<string> cardNames = vector<string>({ "seven","eight","nine","ten","bot","top","king","ace" });
	vector<string> cardColors = vector<string>({ "Acorns","Balls","Green","Heart" });

	vector<unique_ptr<Card>> cards = vector<unique_ptr<Card>>();

	for (auto color : cardColors)
	{
		for (auto name : cardNames)
		{
			string path = buildCardPath(color, name);

			auto texture = move(getCardTexture(path));
			auto functionColor = nameToColor(color);
			auto functionNumber = nameToNumber(name);

			if (name == "seven")
			{
				auto card = make_unique<SevenCard>(functionNumber, functionColor, move(texture));
				cards.push_back(move(card));
			}
			else if (name == "top")
			{
				auto card = make_unique<TopCard>(functionNumber, functionColor, move(texture));
				cards.push_back(move(card));
			}
			else if (name == "ace")
			{
				auto card = make_unique<AceCard>(functionNumber, functionColor, move(texture));
				cards.push_back(move(card));
			}
			else if (name == "bot" && color == "Green")
			{
				auto card = make_unique<GreenBottomCard>(functionNumber, functionColor, move(texture));
				cards.push_back(move(card));
			}
			else 
			{
				auto card = make_unique<Card>(functionNumber, functionColor, move(texture));
				cards.push_back(move(card));
			}
		}
	}

	return cards;
}

shared_ptr<Texture> Opener::getCardBackSide() const
{
	const string backSideImage = "back.jpg";
	auto pathParts = vector<string>{ texturesRoot, cardBackSideRoot, backSideImage };
	string path = buildPath(pathParts);
	auto texture = make_unique<Texture>(Texture());
	texture->loadFromFile(path);
	return texture;
}

vector<shared_ptr<ColorSprite>> Opener::getColorSprites(float screenWidth, float screenHeight) const
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

unique_ptr<Texture> Opener::getMenuTexture(string startImage) const
{
	auto pathParts = vector<string>{ texturesRoot, menuRoot, startImage };
	unique_ptr<Texture> texture = make_unique<Texture>(Texture());
	string path = buildPath(pathParts);
	texture->loadFromFile(path);
	return texture;
}

sf::Texture Opener::getBackgroundTexture() const
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

Button Opener::getButton(const string & text, float width, float height, float positionX, float positionY) const
{
	unique_ptr<Text> buttonText(make_unique<Text>());
	buttonText->setFont(font);
	buttonText->setString(text);
	buttonText->setFillColor(Color::Black);
	Button button = Button(move(getMenuTexture("button.png")), move(buttonText));
	button.setSize(width, height);
	button.setPosition(positionX, positionY);
	return button;
}

