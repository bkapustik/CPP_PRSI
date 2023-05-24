#include "ColorSprite.h"

ColorSprite::ColorSprite(CardFunctionColor color, unique_ptr<Texture> texture)
{
	this->texture = move(texture);
	this->color = color;
	this->sprite = make_unique<Sprite>(Sprite((*this->texture)));
}
