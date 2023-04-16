#pragma once

#include "CardFunctionColor.h"
#include "SFML/Graphics.hpp"
#include "memory"

using namespace std;
using namespace sf;

class ColorSprite
{
public:
	CardFunctionColor color;

	shared_ptr<Sprite> sprite;
	unique_ptr<Texture> texture;

	ColorSprite(CardFunctionColor color, unique_ptr<Texture> texture);
};

