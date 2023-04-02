#pragma once
#include "Player.h"
#include "SFML/System/InputStream.hpp"

class HumanPlayer : public Player
{
private : 
	shared_ptr<Deck> deck;
	bool canUseThisCard(shared_ptr<CardSprite> card, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor> colorToBePlayed, int cardsToTake, int turnsToWait);
	bool isSpriteClicked(shared_ptr<Sprite> sprite);
public:
	bool wantsCustomTurn() override;
	void takeCards(vector<shared_ptr<Card>>& cards) override;
	void removeCard(shared_ptr<Card> cardToRemove) override;
	bool tryPlayACard(shared_ptr<Card>& cardToPlay, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor> colorToBePlayed, int cardsToTake, int turnsToWait) override;
	HumanPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics, shared_ptr<Deck> deck);
	bool tryTakeACard() override;
};