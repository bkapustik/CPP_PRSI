#pragma once

#include "CardFunctionColor.h"
#include "CardFunctionNumber.h"
#include "SFML/Graphics.hpp"
#include "memory"

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
		Card(CardFunctionNumber number, CardFunctionColor color, unique_ptr<sf::Texture> texture);
};

