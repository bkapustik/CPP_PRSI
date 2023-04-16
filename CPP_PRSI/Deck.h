#pragma once
#include <queue>
#include "Card.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Opener.h"
#include "GraphicsHelper.h"

using namespace std;

class Deck
{
public:

	vector<shared_ptr<Sprite>> sprites;
	shared_ptr<Sprite> frontDeckCard;

	Deck(vector<shared_ptr<Card>>& cards, std::shared_ptr<GraphicsHelper> graphics);
	
	void shuffle();
	void print();
	void addACard(shared_ptr<Card> card);

	vector<shared_ptr<Card>> getNCards(int n);
	shared_ptr<Card> showTopCard() const;

private: 
	Vector2f PositionOfFirstCard;
	queue<shared_ptr<Card>> Cards;

	shared_ptr<GraphicsHelper> graphics;
	
	void changeShownCard();
	void vectorToQueue(vector<shared_ptr<Card>>& cards);
	void shuffle(vector<shared_ptr<Card>>& cards);

	vector<shared_ptr<Card>> cardsToVector();

	shared_ptr<Card> deque();
	shared_ptr<Sprite> createBackSprite(int shift);
};