#include "Card.h"

Card::Card(CardFunctionNumber number, CardFunctionColor color, std::unique_ptr<sf::Texture> texture)
{
	Color = color;
	Number = number;
	Texture = std::move(texture);
}
