#include "ColorSprite.h"

ColorSprite::ColorSprite(CardFunctionColor color, unique_ptr<Texture> texture)
{
	this->texture = move(texture);
	this->color = color;
	this->sprite = make_shared<Sprite>(Sprite((*this->texture)));
}
