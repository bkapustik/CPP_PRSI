#include "GameManager.h"

GameManager::GameManager()
{
	
}

GameManager::GameManager(int numberOfPlayers, GameMenuDto & menu, const vector<shared_ptr<ColorSprite>> colorSprites)
{
	numberOfPlayers = 4;
	menu.deck.shuffle();
	NumberOfPlayers = numberOfPlayers;
	this->colorSprites = colorSprites;

	RealPlayer = make_shared<HumanPlayer>(HumanPlayer(Vector2f(menu.graphics.ScreenWidth / 2 - 300, menu.graphics.ScreenHeight - 200), menu.graphics));
	Players.push_back(RealPlayer);
	
	vector<Vector2f> positionOfFirstCardSpriteOfPlayer{ Vector2f(200, 200), Vector2f(menu.graphics.ScreenWidth/2, 200), Vector2f(menu.graphics.ScreenWidth - 300, 200) };

	for (int i = 0; i < numberOfPlayers-1; i++)
	{
		Players.push_back(make_shared<ComputerPlayer>(ComputerPlayer(positionOfFirstCardSpriteOfPlayer[i], menu.graphics)));
	}
	
	PlayerOnTurn = Helper::randomInRange(numberOfPlayers);

	int numberOfCardsAtTheBeginning = 5;

	for (auto player : Players)
	{
		giveNCardsToPlayer(player, numberOfCardsAtTheBeginning, menu);
	}

	playerEvent = notPlaying;
}

void GameManager::giveNCardsToPlayer(shared_ptr<Player> player, int n, GameMenuDto & menu)
{
	vector<unique_ptr<Card>> cardsTaken = menu.deck.getNCards(n);

	player->takeCards(cardsTaken, menu.graphics);
}

void GameManager::removeFinishedPlayer()
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

void GameManager::humanSkip()
{
	gameData.NumberOfPlayersSkippedByAce--;
	userInputReceived = true;
}

void GameManager::humanTakeCards(GameMenuDto & menu)
{
	giveNCardsToPlayer(Players[PlayerOnTurn], gameData.CardsToTake, menu);
	gameData.CardsToTake = 0;
	userInputReceived = true;
}

void GameManager::evaluateCard(unique_ptr<Card> card, GameMenuDto & menu)
{
	card->evaluate(gameData);
	menu.deck.addACard(move(card), menu.graphics);
}

void GameManager::playOneTurn(GameMenuDto & menu, bool & choosingColor)
{
	//makes the player on turn play
	if (NumberOfPlayers <= 1)
	{
		return;
	}
	PlayerOnTurn = PlayerOnTurn % NumberOfPlayers;
	auto playerOnTurn = Players[PlayerOnTurn];

	unique_ptr<Card> playedCard = make_unique<Card>();

	auto topCard = ColorNumber(menu.deck.frontDeckCard->card->Color, menu.deck.frontDeckCard->card->Number);

	playerOnTurn->setOnTurn();
	if (playerOnTurn->wantsCustomTurn() || !userInputReceived)
	{
		if (gameData.NumberOfPlayersSkippedByAce > 0)
		{
			playerEvent = beingSkipped;
		}
		else if (gameData.CardsToTake > 0)
		{
			playerEvent = hasToTakeACard;
		}
		else
		{
			playerEvent = playing;
		}

		userInputReceived = false;
		if (choosingColor)
		{
			if (playerOnTurn->tryChooseAColor(gameData.ColorToBePlayed, colorSprites))
			{
				choosingColor = false;
				userInputReceived = true;
			}
		}

		if (playerOnTurn->tryPlayACard(playedCard, topCard, gameData, choosingColor))
		{
			evaluateCard(move(playedCard), menu);

			if (!choosingColor)
			{
				userInputReceived = true;
			}
		}
		else if (playerOnTurn->tryTakeACard(menu.deck))
		{
			if (gameData.NumberOfPlayersSkippedByAce > 0)
			{
				gameData.NumberOfPlayersSkippedByAce--;
			}
			else
			{
				giveNCardsToPlayer(playerOnTurn, gameData.CardsToTake > 0 ? gameData.CardsToTake : 1, menu);
				gameData.CardsToTake = 0;
			}
			userInputReceived = true;
		}
		playerOnTurn->checkPlayersCards(menu.graphics);
		
		if(playerOnTurn->hasFinished)
		{
			PlayerHasFinished = true;
		}
	}
	else
	{
		playerEvent = notPlaying;
		if (gameData.CardsToTake > 0)
		{
			unique_ptr<Card> cancellingCard = make_unique<Card>();

			if (playerOnTurn->tryCanCancelTakingACard(cancellingCard))
			{
				evaluateCard(move(cancellingCard), menu);
			}
			else
			{
				giveNCardsToPlayer(playerOnTurn, gameData.CardsToTake, menu);
				gameData.CardsToTake = 0;
			}
		}

		else if (gameData.NumberOfPlayersSkippedByAce > 0)
		{
			unique_ptr<Card> cancellingCard = make_unique<Card>();

			if (playerOnTurn->tryCanCancelBeingSkipped(cancellingCard))
			{
				evaluateCard(move(cancellingCard), menu);
			}
			else
			{
				gameData.NumberOfPlayersSkippedByAce--;
			}
		}

		else if (playerOnTurn->tryPlayACard(playedCard, topCard, gameData.TopHasBeenPlayed, gameData.ColorToBePlayed))
		{
			gameData.TopHasBeenPlayed = false;
			
			evaluateCard(move(playedCard), menu);
		}
		else
		{
			//No card to take so the player has to take one
			giveNCardsToPlayer(playerOnTurn, 1, menu);
		}
	}
	playerOnTurn->checkPlayersCards(menu.graphics);
	checkUserInputRecieved(playerOnTurn);
}

void GameManager::checkUserInputRecieved(shared_ptr<Player> & player)
{
	if (userInputReceived)
	{
		if (player->hasFinished)
		{
			removeFinishedPlayer();
		}
		else
		{
			PlayerOnTurn++;
		}
		player->cancelIsOnTurn();
	}
}