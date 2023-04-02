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
	Deck(vector<shared_ptr<Card>>& cards, std::shared_ptr<GraphicsHelper> graphics);
	void shuffle();
	void print();
	vector<shared_ptr<Card>> getNCards(int n);
	void addACard(shared_ptr<Card> card);
	shared_ptr<Card> showTopCard() const;
	vector<shared_ptr<Sprite>> sprites;
	shared_ptr<Sprite> frontDeckCard;

private: 
	shared_ptr<GraphicsHelper> graphics;
	std::queue<shared_ptr<Card>> Cards;
	void shuffle(vector<shared_ptr<Card>>& cards);
	vector<shared_ptr<Card>> cardsToVector();
	void vectorToQueue(vector<shared_ptr<Card>>& cards);
	shared_ptr<Card> dequeue();
	Vector2f PositionOfFirstCard;
	
	void changeShownCard();

	shared_ptr<Sprite> createBackSprite(int shift);
};