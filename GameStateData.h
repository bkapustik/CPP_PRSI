#pragma once

#include <memory>
#include "CardFunctionColor.h"

using namespace std;

class GameStateData
{
public : 
	int CardsToTake;
	int NumberOfPlayersSkippedByAce;
	bool TopHasBeenPlayed;
	
	shared_ptr<CardFunctionColor> ColorToBePlayed;

	GameStateData()
	{
		ColorToBePlayed = make_shared<CardFunctionColor>(CardFunctionColor::heart);
		CardsToTake = 0;
		NumberOfPlayersSkippedByAce = 0;
		TopHasBeenPlayed = false;
	}

    void evaluateCardWithNumberSeven()
    {
        CardsToTake += 3;
    }

    void evaluateLeafBotCard()
    {
        CardsToTake = 0;
    }

    void evaluateTopCard()
    {
        TopHasBeenPlayed = true;
    }

    void evaluateSkippingCard()
    {
        NumberOfPlayersSkippedByAce++;
    }
};