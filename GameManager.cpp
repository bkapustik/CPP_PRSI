#include "GameManager.h"

GameManager::GameManager()
{
	
}

GameManager::GameManager(int numberOfPlayers, shared_ptr<Deck> deck, shared_ptr<GraphicsHelper> graphicsHelper, shared_ptr<bool> choosingColor, vector<shared_ptr<ColorSprite>> colorSprites)
{
	numberOfPlayers = 4;
	deck->shuffle();
	CardsToTake = 0;
	NumberOfPlayersSkippedByAce = 0;
	GameDeck = deck;
	NumberOfPlayers = numberOfPlayers;
	this->colorSprites = colorSprites;
	TopHasBeenPlayed = make_shared<bool>(false);
	ColorToBePlayed = make_shared<CardFunctionColor>(CardFunctionColor::heart);
	graphics = graphicsHelper;

	RealPlayer = make_shared<HumanPlayer>(HumanPlayer(Vector2f(graphics->ScreenWidth / 2 - 300, graphics->ScreenHeight - 200), graphics, deck, choosingColor));
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

	playerEvent = notPlaying;
}

void GameManager::giveNCardsToPlayer(shared_ptr<Player> player, int n)
{
	vector<unique_ptr<Card>> cardsTaken = GameDeck->getNCards(n);

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

void GameManager::evaluateCardTakingCancellingCard(unique_ptr<Card>& card)
{
	if (card->Number == CardFunctionNumber::seven)
	{
		evaluateCardWithNumberSeven();
	}
	else
	{
		evaluateLeafBotCard();
	}
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

void GameManager::evaluatePlayedCard(unique_ptr<Card>& card)
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
}

void GameManager::humanSkip()
{
	NumberOfPlayersSkippedByAce--;
	userInputReceived = true;
	checkUserInputRecieved();
}

void GameManager::humanTakeCards()
{
	giveNCardsToPlayer(Players[PlayerOnTurn], CardsToTake);
	CardsToTake = 0;
	userInputReceived = true;
	checkUserInputRecieved();
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

	unique_ptr<Card> playedCard = make_unique<Card>();

	auto topCard = ColorNumber(GameDeck->frontDeckCard->card->Color, GameDeck->frontDeckCard->card->Number);

	playerOnTurn->setOnTurn();
	if (playerOnTurn->wantsCustomTurn() || !userInputReceived)
	{
		if (NumberOfPlayersSkippedByAce > 0)
		{
			playerEvent = beingSkipped;
		}
		else if (CardsToTake > 0)
		{
			playerEvent = hasToTakeACard;
		}
		else
		{
			playerEvent = playing;
		}

		userInputReceived = false;
		if ((*playerOnTurn->choosingColor))
		{
			if (playerOnTurn->tryChooseAColor(ColorToBePlayed, colorSprites))
			{
				(*playerOnTurn->choosingColor) = false;
				userInputReceived = true;
			}
		}

		if (playerOnTurn->tryPlayACard(playedCard, topCard, TopHasBeenPlayed, ColorToBePlayed, CardsToTake, NumberOfPlayersSkippedByAce))
		{
			evaluatePlayedCard(playedCard);
			if (playedCard->Color == CardFunctionColor::leaf && playedCard->Number == CardFunctionNumber::bot)
			{
				evaluateLeafBotCard();
			}
			if (!(*playerOnTurn->choosingColor))
			{
				userInputReceived = true;
			}
			GameDeck->addACard(move(playedCard));
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
		playerEvent = notPlaying;
		if (CardsToTake > 0)
		{
			unique_ptr<Card> cancellingCard = make_unique<Card>();

			if (playerOnTurn->tryCanCancelTakingACard(cancellingCard, topCard))
			{
				evaluateCardTakingCancellingCard(cancellingCard);
				GameDeck->addACard(move(cancellingCard));
			}
			else
			{
				giveNCardsToPlayer(playerOnTurn, CardsToTake);
				CardsToTake = 0;
			}
		}

		else if (NumberOfPlayersSkippedByAce > 0)
		{
			unique_ptr<Card> cancellingCard = make_unique<Card>();

			if (playerOnTurn->tryCanCancelBeingSkipped(cancellingCard, topCard))
			{
				evaluateSkippingCard();
				GameDeck->addACard(move(cancellingCard));
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
			GameDeck->addACard(move(playedCard));
		}
		else
		{
			//No card to take so the player has to take one
			giveNCardsToPlayer(playerOnTurn, 1);
		}
	}
	playerOnTurn->checkPlayersCards();
	checkUserInputRecieved();
}

void GameManager::checkUserInputRecieved()
{
	auto playerOnTurn = Players[PlayerOnTurn];
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

		if (RealPlayer->hasFinished)
		{
			PlayerHasFinished = true;
		}
	}
}