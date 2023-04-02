#pragma once
#include "Card.h"
#include "memory"

using namespace std;
using namespace sf;


class CardSprite
{
	public: 
		shared_ptr<Card> card;
		shared_ptr<Sprite> sprite;

		CardSprite(shared_ptr<Card> card, shared_ptr<Sprite> sprite);
};

