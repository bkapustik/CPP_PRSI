#include "CardSprite.h"

CardSprite::CardSprite(shared_ptr<Card> card, shared_ptr<Sprite> sprite)
{
	this->card = card;
	this->sprite = sprite;
}