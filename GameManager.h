#pragma once
#include "Player.h"
#include "Deck.h"
#include "Helper.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GraphicsHelper.h"

enum PlayerEvent
{
	beingSkipped, hasToTakeACard, playing, notPlaying
};

class GameManager
{
private:
	
	int NumberOfPlayers;
	int PlayerOnTurn;
	int CardsToTake;
	int NumberOfPlayersSkippedByAce;

	shared_ptr<bool> TopHasBeenPlayed;
	shared_ptr<CardFunctionColor> ColorToBePlayed;
	shared_ptr<HumanPlayer> RealPlayer;

	void evaluateCardTakingCancellingCard(const unique_ptr<Card>& card);
	void evaluateSkippingCard();
	void evaluateCardWithNumberSeven();
	void evaluateTopCard();
	void evaluateLeafBotCard();
	void giveNCardsToPlayer(shared_ptr<Player> player, int n, Deck & deck, GraphicsHelper & graphics);
	void removeFinishedPlayer();
	void checkUserInputRecieved();
	void evaluatePlayedCard(const unique_ptr<Card>& card);
public:
	GameManager();
	GameManager(int numberOfPlayers, Deck & deck, GraphicsHelper & graphics, const vector<shared_ptr<ColorSprite>> colorSprites);
	
	bool PlayerHasFinished = false;
	bool userInputReceived = true;

	PlayerEvent playerEvent;

	vector<shared_ptr<ColorSprite>> colorSprites;
	vector<shared_ptr<Player>> Players;
	
	void playOneTurn(GraphicsHelper & graphics, Deck & deck, bool & choosingColor);
	void humanSkip();
	void humanTakeCards(GraphicsHelper & graphics, Deck & deck);
};

