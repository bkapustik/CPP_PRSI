#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Card.h"

using namespace std;
using namespace sf;

class GraphicsHelper
{
public : 
	float CardDecreaseWidthBy = 2;
	float CardDecreaseHeightBy = 2;
	float CardHeight;
	float CardWidth;
	float ScreenHeight;
	float ScreenWidth;
	Font font;
	shared_ptr<Texture> backCardSideTexture;

	GraphicsHelper(
		float cardDecreaseWidthBy, float cardDecreaseHeightBy,
		float screenWidth, float screenHeight,
		shared_ptr<Card> firstCard,
		shared_ptr<Texture> backCardSideTexture
	);
	void scaleCardSize(shared_ptr<Sprite> card);
	void setPositionRelativeToCardSize(shared_ptr<Sprite> card, float width, float height);

	Text getText(string text);
};

