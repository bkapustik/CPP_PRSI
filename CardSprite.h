#pragma once
#include "Card.h"
#include "memory"

using namespace std;
using namespace sf;


class CardSprite
{
	public: 
		unique_ptr<Card> card;
		unique_ptr<Sprite> sprite;

		CardSprite();
		CardSprite(unique_ptr<Card> card);
};

