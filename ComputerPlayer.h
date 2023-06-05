#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
	public:
		ComputerPlayer(const Vector2f positionOfFirstCard, GraphicsHelper & graphics);
		ComputerPlayer() : Player()
		{}
		bool tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, GameStateData & gameData, bool & choosingColor) override
		{
			return false;
		}
		bool wantsCustomTurn() const override;
};

