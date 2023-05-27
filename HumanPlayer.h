#pragma once
#include "Player.h"
#include "SFML/System/InputStream.hpp"

class HumanPlayer : public Player
{
private : 
	shared_ptr<Deck> deck;
	
	bool canUseThisCard(CardSprite& card, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait);
	bool isSpriteClicked(const unique_ptr<Sprite>& sprite) const;
	bool isSpriteClicked(const Sprite& sprite) const;
public:
	HumanPlayer(const Vector2f positionOfFirstCard, const shared_ptr<GraphicsHelper> graphics, const shared_ptr<Deck> deck, const shared_ptr<bool> choosingColor);
	
	void takeCards(vector<unique_ptr<Card>>& cards) override;
	
	void checkPlayersCards() override;
	bool wantsCustomTurn() const override;
	bool tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait) override;
	bool tryTakeACard() override;
	bool tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, const vector<shared_ptr<ColorSprite>> & colorOptions) override;
};