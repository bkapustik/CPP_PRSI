#include "CardSprite.h"

CardSprite::CardSprite()
{
	this->card = make_unique<Card>();
	this->sprite = make_unique<Sprite>((*this->card->Texture));
}

CardSprite::CardSprite(unique_ptr<Card> card)
{
	this->card = move(card);
	this->sprite = make_unique<Sprite>((*this->card->Texture));
}