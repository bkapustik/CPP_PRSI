#pragma once
#include <queue>
#include "Card.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Opener.h"
#include "GraphicsHelper.h"
#include <random>
#include "CardSprite.h"

using namespace std;

class Deck
{
public:
	
	vector<unique_ptr<Sprite>> sprites;
	unique_ptr<CardSprite> frontDeckCard;

	Deck(vector<unique_ptr<Card>>& cards, const std::shared_ptr<GraphicsHelper> graphics);
	
	void shuffle();
	void addACard(unique_ptr<Card> card);

	vector<unique_ptr<Card>> getNCards(int n);

private: 
	Vector2f PositionOfFirstCard;
	queue<unique_ptr<Card>> Cards;

	shared_ptr<GraphicsHelper> graphics;
	
	void vectorToQueue(vector<unique_ptr<Card>>& cards);
	void changeShownCard();
	void shuffle(vector<shared_ptr<Card>>& cards);

	vector<unique_ptr<Card>> cardsToVector();

	unique_ptr<Card> deque();
	Sprite createBackSprite(const int shift);
};