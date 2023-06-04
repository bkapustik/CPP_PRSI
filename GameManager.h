#pragma once
#include "Player.h"
#include "Deck.h"
#include "Helper.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GraphicsHelper.h"
#include "GameStateData.h"
#include "GameMenuDto.h"

enum PlayerEvent
{
	beingSkipped, hasToTakeACard, playing, notPlaying
};

class GameManager
{
private:
	
	int NumberOfPlayers;
	int PlayerOnTurn;

	GameStateData gameData;
	
	shared_ptr<HumanPlayer> RealPlayer;

	void giveNCardsToPlayer(shared_ptr<Player> player, int n, GameMenuDto & menu);
	void removeFinishedPlayer();
	void checkUserInputRecieved(shared_ptr<Player> & player);
	void evaluateCard(unique_ptr<Card> card, GameMenuDto & menu);
public:
	GameManager();
	GameManager(int numberOfPlayers, GameMenuDto & menu, const vector<shared_ptr<ColorSprite>> colorSprites);
	
	bool PlayerHasFinished = false;
	bool userInputReceived = true;

	PlayerEvent playerEvent;

	vector<shared_ptr<ColorSprite>> colorSprites;
	vector<shared_ptr<Player>> Players;
	
	void playOneTurn(GameMenuDto & menu, bool & choosingColor);
	void humanSkip();
	void humanTakeCards(GameMenuDto & menu);
};