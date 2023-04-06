#pragma once
#include "Player.h"
#include "Deck.h"
#include "Helper.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GraphicsHelper.h"

class GameManager
{
private:
	shared_ptr<Deck> GameDeck;

	shared_ptr<HumanPlayer> RealPlayer;
	int NumberOfPlayers;
	int PlayerOnTurn;
	int CardsToTake;
	int NumberOfPlayersSkippedByAce;

	shared_ptr<GraphicsHelper> graphics;

	shared_ptr<bool> TopHasBeenPlayed;
	shared_ptr<CardFunctionColor> ColorToBePlayed;

	void evaluateCardTakingCancellingCard(shared_ptr<Card> card);
	void evaluateSkippingCard();
	void evaluateCardWithNumberSeven();
	void evaluateTopCard();
	void evaluateLeafBotCard();
	void giveNCardsToPlayer(shared_ptr<Player> player, int n);
	void removeFinishedPlayer(shared_ptr<Player> player);
	void evaluatePlayedCard(shared_ptr<Card> card);
public : 
	GameManager(int numberOfPlayers, shared_ptr<Deck> deck, shared_ptr<GraphicsHelper> graphicsHelper);
	
	bool userInputReceived = true;
	vector<shared_ptr<Player>> Players;
	void evaluatePlayerPressEvent();
	void playOneTurn();
	bool PlayerHasFinished;
};

