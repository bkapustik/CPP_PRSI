#pragma once
#include <vector>
#include "Card.h"
#include "Deck.h"
#include <memory>
#include "Helper.h"
#include "CardSprite.h"
#include "ColorNumber.h"

class Player
{
private:
	bool isOnTurn;
	bool tryReturnCardOfColor(CardFunctionColor color, unique_ptr<Card>& card);
	bool tryReturnCardOfNumber(CardFunctionNumber number, unique_ptr<Card>& card);
	bool tryReturnCardOfColorAndNumber(CardFunctionColor color, CardFunctionNumber number, unique_ptr<Card>& cardToReturn);
	

public:
	bool hasFinished;
	shared_ptr<bool> choosingColor;
	CardFunctionColor getRandomColor();
	
	bool virtual tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, vector<shared_ptr<ColorSprite>> colorOptions)
	{
		return false;
	}

	bool virtual tryPlayACard(unique_ptr<Card>& cardToPlay, ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait)
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
	void virtual takeCards(vector<unique_ptr<Card>>& cards);
	void setOnTurn();
	bool virtual wantsCustomTurn()
	{
		return false;
	}
	void cancelIsOnTurn();
	bool tryCanCancelTakingACard(unique_ptr<Card>& cancellingCard, ColorNumber& topDeckCard);
	bool tryCanCancelBeingSkipped(unique_ptr<Card>& cancellingCard, ColorNumber& topDeckCard);
	bool virtual tryPlayACard(unique_ptr<Card>& card, ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed);
	void virtual checkPlayersCards();
};