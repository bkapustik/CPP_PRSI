#pragma once
#include <vector>
#include "Card.h"
#include "Deck.h"
#include <memory>
#include "Helper.h"
#include "CardSprite.h"

class Player
{
private:
	bool isOnTurn;
	bool tryReturnCardOfColor(CardFunctionColor color, shared_ptr<Card>& card);
	bool tryReturnCardOfNumber(CardFunctionNumber number, shared_ptr<Card>& card);
	bool tryReturnCardOfColorAndNumber(CardFunctionColor color, CardFunctionNumber number, shared_ptr<Card>& cardToReturn);
	CardFunctionColor getRandomColor();

public:
	bool hasFinished;

	
	bool virtual tryPlayACard(shared_ptr<Card>& cardToPlay, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor> colorToBePlayed, int cardsToTake, int turnsToWait)
	{
		return false;
	}

	bool virtual tryTakeACard()
	{
		return false;
	}

	Vector2f PositionOfFirstCard;
	shared_ptr<GraphicsHelper> graphics;
	Player(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics);
	vector<CardSprite> cards;
	void virtual takeCards(vector<shared_ptr<Card>>& cards);
	void setOnTurn();
	bool virtual wantsCustomTurn()
	{
		return false;
	}
	void cancelIsOnTurn();
	bool tryCanCancelTakingACard(shared_ptr<Card>& cancellingCard, shared_ptr<Card> topDeckCard);
	bool tryCanCancelBeingSkipped(shared_ptr<Card>& cancellingCard, shared_ptr<Card> topDeckCard);
	bool virtual tryPlayACard(shared_ptr<Card>& card, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed);
	void virtual removeCard(shared_ptr<Card> cardToRemove);
};