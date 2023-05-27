#include "GraphicsHelper.h"

GraphicsHelper::GraphicsHelper(
	float cardDecreaseWidthBy, 
	float cardDecreaseHeightBy,
	float screenWidth,
	float screenHeight,
	const Card & firstCard,
	const shared_ptr<Texture> backCardSideTexture
)
{
	CardDecreaseWidthBy = cardDecreaseWidthBy;
	CardDecreaseHeightBy = cardDecreaseHeightBy;
	CardWidth = firstCard.Texture->getSize().x / CardDecreaseWidthBy;
	CardHeight = firstCard.Texture->getSize().y / CardDecreaseHeightBy;
	ScreenHeight = screenHeight;
	ScreenWidth = screenWidth;
	this->backCardSideTexture = backCardSideTexture;
	font = Font();
	font.loadFromFile("../Fonts/videotype.otf");
}

void GraphicsHelper::scaleCardSize(Sprite& card)
{
	card.setScale(1 / (float)CardDecreaseWidthBy, 1 / (float)CardDecreaseHeightBy);
}

void GraphicsHelper::scaleCardSize(unique_ptr<Sprite>& card)
{
	card->setScale(1 / (float)CardDecreaseWidthBy, 1 / (float)CardDecreaseHeightBy);
}

void GraphicsHelper::setPositionRelativeToCardSize(unique_ptr<Sprite>& card, float width, float height)
{
	card->setPosition(width - CardWidth / 2, height - CardHeight / 2);
}

void GraphicsHelper::setPositionRelativeToCardSize(Sprite& card, float width, float height)
{
	card.setPosition(width - CardWidth / 2, height - CardHeight / 2);
}

Text GraphicsHelper::getText(const string & toDisplay)
{
	Text text;
	text.setFont(font);
	text.setString(toDisplay);
	text.setCharacterSize(100);
	text.setFillColor(Color::Red);
	return text;
}