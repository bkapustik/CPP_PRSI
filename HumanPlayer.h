#pragma once
#include "Player.h"
#include "SFML/System/InputStream.hpp"

class HumanPlayer : public Player
{
private : 
	shared_ptr<Deck> deck;
	
	bool canUseThisCard(CardSprite& card, ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait);
	bool isSpriteClicked(unique_ptr<Sprite>& sprite);
	bool isSpriteClicked(Sprite& sprite);
public:
	HumanPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics, shared_ptr<Deck> deck, shared_ptr<bool> choosingColor);
	
	void takeCards(vector<unique_ptr<Card>>& cards) override;
	
	void checkPlayersCards() override;
	bool wantsCustomTurn() override;
	bool tryPlayACard(unique_ptr<Card>& cardToPlay, ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait) override;
	bool tryTakeACard() override;
	bool tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, vector<shared_ptr<ColorSprite>> colorOptions) override;
};