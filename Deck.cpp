#include "Deck.h"

#include <iostream>

using namespace std;

Sprite Deck::createBackSprite(const int shift, GraphicsHelper & graphics)
{
	auto newSprite = Sprite((*graphics.backCardSideTexture));

	graphics.scaleCardSize(newSprite);
	graphics.setPositionRelativeToCardSize(newSprite, PositionOfFirstCard.x + 10 * shift, PositionOfFirstCard.y);

	return newSprite;
}

void Deck::changeShownCard(GraphicsHelper & graphics)
{
	graphics.scaleCardSize((*frontDeckCard->sprite));
	graphics.setPositionRelativeToCardSize((*frontDeckCard->sprite), graphics.ScreenWidth / 2, graphics.ScreenHeight / 2);
}

Deck::Deck(vector<unique_ptr<Card>>& cards, GraphicsHelper & graphics)
{
	this->PositionOfFirstCard = Vector2f(graphics.ScreenWidth / 2 + 200, graphics.ScreenHeight / 2);
	sprites = vector<unique_ptr<Sprite>>();

	random_device rd;
	mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);

	for (int i = 0;i < cards.size() - 1; i++)
	{
		Cards.push(move(cards[i]));
		auto newSprite = make_unique<Sprite>(createBackSprite(i, graphics));
		sprites.push_back(move(newSprite));
	}

	frontDeckCard = make_unique<CardSprite>(move(cards[cards.size() - 1]));
	changeShownCard(graphics);
}

void Deck::shuffle(vector<shared_ptr<Card>>& cards)
{
	srand(time(0));
	random_shuffle(cards.begin(), cards.end());
}

void Deck::shuffle()
{
	auto cards = cardsToVector();

	random_device rd;
	mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);

	vectorToQueue(cards);
}

vector<unique_ptr<Card>> Deck::cardsToVector()
{
	vector<unique_ptr<Card>> cards = vector<unique_ptr<Card>>();

	while (Cards.size() > 0)
	{
		cards.push_back(move(Cards.front()));
		Cards.pop();
	}
	 
	return cards;
}

void Deck::vectorToQueue(vector<unique_ptr<Card>>& cards)
{
	for (auto& card : cards)
	{
		Cards.push(move(card));
	}
}

vector<unique_ptr<Card>> Deck::getNCards(int n)
{
	vector<unique_ptr<Card>> cards = vector<unique_ptr<Card>>();

	//can not start with card at the start of the deck
	for (int i = 0; i < n; i++)
	{
		if (Cards.size() > 1)
		{
			auto card = move(Cards.front());
			Cards.pop();
			cards.push_back(move(card));
			sprites.erase(sprites.begin());
		}
	}
	return cards;
}

void Deck::addACard(unique_ptr<Card> card, GraphicsHelper & graphics)
{
	Cards.push(move(frontDeckCard->card));
	frontDeckCard = make_unique<CardSprite>(move(card));
	changeShownCard(graphics);
	auto newSprite = make_unique<Sprite>(createBackSprite(sprites.size() - 1, graphics));
	sprites.push_back(move(newSprite));
}

