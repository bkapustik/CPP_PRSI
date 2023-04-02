#pragma once

#include "CardFunctionColor.h"
#include "CardFunctionNumber.h"
#include "SFML/Graphics.hpp"
#include "memory"

class Card
{
	public :
		CardFunctionColor Color;
		CardFunctionNumber Number;
		std::unique_ptr<sf::Texture> Texture;
		
		Card(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture);
};

