#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
	public:
		ComputerPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics);

		bool tryPlayACard(unique_ptr<Card>& cardToPlay, ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait) override
		{
			return false;
		}
		bool wantsCustomTurn() override;
};

