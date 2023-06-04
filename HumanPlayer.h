#pragma once
#include "Player.h"
#include "SFML/System/InputStream.hpp"
#include "GameStateData.h"

class HumanPlayer : public Player
{
private : 
	bool canUseThisCard(CardSprite& card, const ColorNumber& topDeckCard, GameStateData & gameData);
	bool isSpriteClicked(const unique_ptr<Sprite>& sprite) const;
	bool isSpriteClicked(const Sprite& sprite) const;
public:
	HumanPlayer(const Vector2f positionOfFirstCard, GraphicsHelper & graphics);
	
	void takeCards(vector<unique_ptr<Card>>& cards, GraphicsHelper & graphics) override;
	
	void checkPlayersCards(GraphicsHelper & graphics) override;
	bool wantsCustomTurn() const override;
	bool tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, GameStateData & gameData, bool & choosingColor) override;
	bool tryTakeACard(Deck & deck) override;
	bool tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, const vector<shared_ptr<ColorSprite>> & colorOptions) override;
};