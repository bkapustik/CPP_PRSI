#include "GameManager.h"

GameManager::GameManager(int numberOfPlayers, shared_ptr<Deck> deck, shared_ptr<GraphicsHelper> graphicsHelper)
{
	numberOfPlayers = 4;
	deck->shuffle();
	CardsToTake = 0;
	NumberOfPlayersSkippedByAce = 0;
	GameDeck = deck;
	NumberOfPlayers = numberOfPlayers;

	TopHasBeenPlayed = make_shared<bool>(false);

	graphics = graphicsHelper;

	RealPlayer = make_shared<HumanPlayer>(HumanPlayer(Vector2f(graphics->ScreenWidth / 2 - 300, graphics->ScreenHeight - 200), graphics, deck));
	Players.push_back(RealPlayer);
	
	vector<Vector2f> positionOfFirstCardSpriteOfPlayer{ Vector2f(200, 200), Vector2f(graphics->ScreenWidth/2, 200), Vector2f(graphics->ScreenWidth - 300, 200) };

	for (int i = 0; i < numberOfPlayers-1; i++)
	{
		Players.push_back(make_shared<ComputerPlayer>(ComputerPlayer(positionOfFirstCardSpriteOfPlayer[i], graphics)));
	}
	
	PlayerOnTurn = Helper::randomInRange(numberOfPlayers);

	int numberOfCardsAtTheBeginning = 5;

	for (auto player : Players)
	{
		giveNCardsToPlayer(player, numberOfCardsAtTheBeginning);
	}
}

void GameManager::giveNCardsToPlayer(shared_ptr<Player> player, int n)
{
	vector<shared_ptr<Card>> cardsTaken = GameDeck->getNCards(n);

	player->takeCards(cardsTaken);
}

void GameManager::evaluateCardWithNumberSeven()
{
	CardsToTake += 3;
}

void GameManager::evaluateLeafBotCard()
{
	CardsToTake = 0;
}

void GameManager::evaluateCardTakingCancellingCard(shared_ptr<Card> card)
{
	if (card->Number == CardFunctionNumber::seven)
	{
		evaluateCardWithNumberSeven();
	}
	else
	{
		evaluateLeafBotCard();
	}
	GameDeck->addACard(card);
}

void GameManager::evaluateSkippingCard()
{
	NumberOfPlayersSkippedByAce++;
}

void GameManager::removeFinishedPlayer(shared_ptr<Player> player)
{
	vector<shared_ptr<Player>> newPlayersInGame = vector<shared_ptr<Player>>();
	for (int i = 0; i < PlayerOnTurn; i++)
	{
		newPlayersInGame.push_back(Players[i]);
	}
	for (int i = PlayerOnTurn + 1; i < NumberOfPlayers; i++)
	{
		newPlayersInGame.push_back(Players[i]);
	}
	NumberOfPlayers--;
	PlayerOnTurn = PlayerOnTurn % NumberOfPlayers;
	Players = newPlayersInGame;
}

void GameManager::evaluateTopCard()
{
	(*TopHasBeenPlayed) = true;
}

void GameManager::evaluatePlayedCard(shared_ptr<Card> card)
{
	if (card->Number == CardFunctionNumber::seven)
	{
		evaluateCardWithNumberSeven();
	}
	else if (card->Number == CardFunctionNumber::top)
	{
		//No need to change desired color. It was changed when we executed tryPlayACard() on player
		evaluateTopCard();
	}
	else if (card->Number == CardFunctionNumber::ace)
	{
		evaluateSkippingCard();
	}
	GameDeck->addACard(card);
}

void GameManager::playOneTurn()
{
	//makes the player on turn play
	if (NumberOfPlayers <= 1)
	{
		return;
	}
	PlayerOnTurn = PlayerOnTurn % NumberOfPlayers;
	auto playerOnTurn = Players[PlayerOnTurn];

	shared_ptr<Card> playedCard;
	auto topCard = GameDeck->showTopCard();

	playerOnTurn->setOnTurn();
	if (playerOnTurn->wantsCustomTurn() || !userInputReceived)
	{
		userInputReceived = false;
		if (playerOnTurn->tryPlayACard(playedCard, topCard, TopHasBeenPlayed, ColorToBePlayed, CardsToTake, NumberOfPlayersSkippedByAce))
		{
			evaluatePlayedCard(playedCard);
			playerOnTurn->removeCard(playedCard);
			userInputReceived = true;
		}
		else if (playerOnTurn->tryTakeACard())
		{
			if (NumberOfPlayersSkippedByAce > 0)
			{
				NumberOfPlayersSkippedByAce--;
			}
			else
			{
				giveNCardsToPlayer(playerOnTurn, CardsToTake > 0 ? CardsToTake : 1);
				CardsToTake = 0;
			}
			userInputReceived = true;
		}
	}
	else
	{

		if (CardsToTake > 0)
		{
			shared_ptr<Card> cancellingCard;

			if (playerOnTurn->tryCanCancelTakingACard(cancellingCard, topCard))
			{
				evaluateCardTakingCancellingCard(cancellingCard);
				playerOnTurn->removeCard(cancellingCard);
			}
			else
			{
				giveNCardsToPlayer(playerOnTurn, CardsToTake);
				CardsToTake = 0;
			}
		}

		else if (NumberOfPlayersSkippedByAce > 0)
		{
			shared_ptr<Card> cancellingCard;

			if (playerOnTurn->tryCanCancelBeingSkipped(cancellingCard, topCard))
			{
				evaluateSkippingCard();
				GameDeck->addACard(cancellingCard);
				playerOnTurn->removeCard(cancellingCard);
			}
			else
			{
				NumberOfPlayersSkippedByAce--;
			}
		}

		else if (playerOnTurn->tryPlayACard(playedCard, topCard, TopHasBeenPlayed, ColorToBePlayed))
		{
			TopHasBeenPlayed = make_shared<bool>(false);
			evaluatePlayedCard(playedCard);
			playerOnTurn->removeCard(playedCard);
		}
		else
		{
			//No card to take so the player has to take one
			giveNCardsToPlayer(playerOnTurn, 1);
		}
	}
	if (userInputReceived)
	{
		if (playerOnTurn->hasFinished)
		{
			removeFinishedPlayer(playerOnTurn);
		}
		else
		{
			PlayerOnTurn++;
		}
		playerOnTurn->cancelIsOnTurn();
	}
}