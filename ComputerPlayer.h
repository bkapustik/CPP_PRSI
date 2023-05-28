#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
	public:
		ComputerPlayer(const Vector2f positionOfFirstCard, GraphicsHelper & graphics);

		bool tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait) override
		{
			return false;
		}
		bool wantsCustomTurn() const override;
};

