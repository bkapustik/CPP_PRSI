#include "Button.h"

Button::Button(unique_ptr<Texture> texture, shared_ptr<Text> text)
{
	this->texture = move(texture);
	this->text = text;
	this->sprite = make_shared<Sprite>(Sprite((*this->texture)));
}

void Button::setPosition(float width, float height)
{
	float spriteWidth = sprite->getGlobalBounds().width;
	float spriteHeight = sprite->getGlobalBounds().height;

	float textWidth = text->getGlobalBounds().width;
	float textHeight = text->getGlobalBounds().height;

	float spritePosX = width - spriteWidth / 2;
	float spritePosY = height - spriteHeight / 2;

	this->sprite->setPosition(spritePosX, spritePosY);
	this->text->setPosition(spritePosX + spriteWidth/2 - textWidth/2, spritePosY + spriteHeight/2 - textHeight/2);
}

void Button::setSize(float width, float height)
{
	auto currWidth = sprite->getGlobalBounds().width;
	auto currHeight = sprite->getGlobalBounds().height;

	auto xMultiplier = width / currWidth;
	auto yMultiplier = height / currHeight;

	sprite->setScale(xMultiplier, yMultiplier);

	text->setCharacterSize(height / 5);
}
