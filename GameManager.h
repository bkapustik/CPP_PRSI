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

	shared_ptr<GraphicsHelper> graphics;
	shared_ptr<bool> TopHasBeenPlayed;
	shared_ptr<CardFunctionColor> ColorToBePlayed;
	shared_ptr<Deck> GameDeck;
	shared_ptr<HumanPlayer> RealPlayer;

	void evaluateCardTakingCancellingCard(const unique_ptr<Card>& card);
	void evaluateSkippingCard();
	void evaluateCardWithNumberSeven();
	void evaluateTopCard();
	void evaluateLeafBotCard();
	void giveNCardsToPlayer(shared_ptr<Player> player, int n);
	void removeFinishedPlayer();
	void checkUserInputRecieved();
	void evaluatePlayedCard(const unique_ptr<Card>& card);
public:
	GameManager();
	GameManager(int numberOfPlayers, shared_ptr<Deck> deck, const shared_ptr<GraphicsHelper> graphicsHelper, shared_ptr<bool> choosingColor, const vector<shared_ptr<ColorSprite>> colorSprites);
	
	bool PlayerHasFinished = false;
	bool userInputReceived = true;

	PlayerEvent playerEvent;

	vector<shared_ptr<ColorSprite>> colorSprites;
	vector<shared_ptr<Player>> Players;
	
	void playOneTurn();
	void humanSkip();
	void humanTakeCards();
};

