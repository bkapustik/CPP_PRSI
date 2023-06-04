#pragma once

#include "CardFunctionColor.h"
#include "CardFunctionNumber.h"
#include "SFML/Graphics.hpp"
#include "memory"
#include "GameStateData.h"

using namespace std;

class Card
{
	public :
		CardFunctionColor Color;
		CardFunctionNumber Number;

		unique_ptr<sf::Texture> Texture;
		
		Card() 
		{
			Number = CardFunctionNumber::seven;
			Color = CardFunctionColor::leaf;
			Texture = make_unique<sf::Texture>(sf::Texture());
		}
		Card(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture);
		void virtual evaluate(GameStateData & gameData)
		{
			
		}
};

class TopCard : public Card
{
public:
	TopCard(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture) : Card(number, color, move(texture))
	{
		
	}

	void evaluate(GameStateData & gameData) override
	{
		gameData.evaluateTopCard();
	}
};

class AceCard : public Card
{
public:
	AceCard(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture) : Card(number, color, move(texture))
	{
		
	}

	void evaluate(GameStateData & gameData) override
	{
		gameData.evaluateSkippingCard();
	}
};

class SevenCard : public Card
{
public:
	SevenCard(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture) : Card(number, color, move(texture))
	{
		
	}

	void evaluate(GameStateData & gameData) override
	{
		gameData.evaluateCardWithNumberSeven();
	}
};

class GreenBottomCard : public Card
{
public:
	GreenBottomCard(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture) : Card(number, color, move(texture))
	{
		
	}

	void evaluate(GameStateData & gameData) override
	{
		gameData.evaluateLeafBotCard();
	}
};