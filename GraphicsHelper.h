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

	GraphicsHelper
	(
		float cardDecreaseWidthBy, 
		float cardDecreaseHeightBy,
		float screenWidth,
		float screenHeight,
		const Card & firstCard,
		const shared_ptr<Texture> backCardSideTexture
	);

	void scaleCardSize(unique_ptr<Sprite>& card);
	void scaleCardSize(Sprite& card);
	void setPositionRelativeToCardSize(unique_ptr<Sprite>& card, float width, float height);
	void setPositionRelativeToCardSize(Sprite& card, float width, float height);

	Text getText(const string & toDisplay);
};

