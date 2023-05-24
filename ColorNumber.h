#pragma once

#include "CardFunctionNumber.h"
#include "CardFunctionColor.h"

class ColorNumber
{
public:
	CardFunctionColor Color;
	CardFunctionNumber Number;

	ColorNumber(CardFunctionColor color, CardFunctionNumber number)
	{
		this->Color = color;
		this->Number = number;
	}
};

