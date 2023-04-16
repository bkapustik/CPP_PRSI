#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
	public:
		ComputerPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics);

		bool tryPlayACard(shared_ptr<Card>& cardToPlay, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait) override
		{
			return false;
		}
		bool wantsCustomTurn() override;
};

