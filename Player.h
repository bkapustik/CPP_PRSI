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
	bool tryReturnCardOfColor(const CardFunctionColor color, unique_ptr<Card>& card);
	bool tryReturnCardOfNumber(const CardFunctionNumber number, unique_ptr<Card>& card);
	bool tryReturnCardOfColorAndNumber(const CardFunctionColor& color, const CardFunctionNumber& number, unique_ptr<Card>& cardToReturn);
	

public:
	bool hasFinished;
	CardFunctionColor getRandomColor() const;
	
	bool virtual tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, const vector<shared_ptr<ColorSprite>> & colorOptions)
	{
		return false;
	}

	bool virtual tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, bool & topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait, bool & choosingColor)
	{
		return false;
	}
	bool virtual tryTakeACard(Deck & deck)
	{
		return false;
	}

	Vector2f PositionOfFirstCard;
	Player(const Vector2f positionOfFirstCard, GraphicsHelper & graphics);
	vector<CardSprite> cards;
	void virtual takeCards(vector<unique_ptr<Card>>& cards, GraphicsHelper & graphics);
	void setOnTurn();
	bool virtual wantsCustomTurn() const
	{
		return false;
	}
	void cancelIsOnTurn();
	bool tryCanCancelTakingACard(unique_ptr<Card>& cancellingCard);
	bool tryCanCancelBeingSkipped(unique_ptr<Card>& cancellingCard);
	bool virtual tryPlayACard(unique_ptr<Card>& card, const ColorNumber& topDeckCard, bool & topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed);
	void virtual checkPlayersCards(GraphicsHelper & graphics);
};