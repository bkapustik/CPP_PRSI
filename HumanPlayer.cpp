#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(const Vector2f positionOfFirstCard, const shared_ptr<GraphicsHelper> graphics, const shared_ptr<Deck> deck, const shared_ptr<bool> choosingColor) : Player(positionOfFirstCard, graphics)
{
	this->deck = deck;
	this->choosingColor = choosingColor;
}

bool HumanPlayer::tryChooseAColor(shared_ptr<CardFunctionColor> colorToBePlayed, const vector<shared_ptr<ColorSprite>> & colorOptions)
{
	for (auto color : colorOptions)
	{
		if (isSpriteClicked(color->sprite))
		{
			(*colorToBePlayed) = color->color;
			return true;
		}
	}
	return false;
}
	
void HumanPlayer::takeCards(vector<unique_ptr<Card>>& cards)
{
	for (int i = 0; i < this->cards.size(); i++)
	{
		graphics->setPositionRelativeToCardSize(this->cards[i].sprite, PositionOfFirstCard.x + i * 100, PositionOfFirstCard.y);
	}
	for (int i = 0; i < cards.size(); ++i)
	{
		CardSprite cardSprite = CardSprite(move(cards[i]));
		graphics->scaleCardSize(cardSprite.sprite);
		graphics->setPositionRelativeToCardSize(cardSprite.sprite, PositionOfFirstCard.x + this->cards.size() * 100, PositionOfFirstCard.y);
		this->cards.push_back(move(cardSprite));
	}
}

void HumanPlayer::checkPlayersCards()
{
	for (int i = 0; i < cards.size(); i++)
	{
		graphics->setPositionRelativeToCardSize(cards[i].sprite, PositionOfFirstCard.x + i * 100, PositionOfFirstCard.y);
	}
	if (cards.empty())
	{
		hasFinished = true;
	}
}

bool HumanPlayer::isSpriteClicked(const unique_ptr<Sprite>& sprite) const
{
	if (Mouse::getPosition().x > sprite->getPosition().x
		&& Mouse::getPosition().x < sprite->getPosition().x + sprite->getGlobalBounds().width
		&& Mouse::getPosition().y > sprite->getPosition().y
		&& Mouse::getPosition().y < sprite->getPosition().y + sprite->getGlobalBounds().height
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HumanPlayer::isSpriteClicked(const Sprite& sprite) const
{
	if (Mouse::getPosition().x > sprite.getPosition().x
		&& Mouse::getPosition().x < sprite.getPosition().x + sprite.getGlobalBounds().width
		&& Mouse::getPosition().y > sprite.getPosition().y
		&& Mouse::getPosition().y < sprite.getPosition().y + sprite.getGlobalBounds().height
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HumanPlayer::wantsCustomTurn() const
{
	return true;
}

bool HumanPlayer::canUseThisCard(CardSprite& card, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait)
{
	if ((*topHasBeenPlayed))
	{
		if (colorToBePlayed)
		{
			if (card.card->Color == (*colorToBePlayed))
			{
				return true;
			}
		}
		if (card.card->Number == CardFunctionNumber::top)
		{
			return true;
		}
		return false;
	}
	if (cardsToTake > 0)
	{
		if (card.card->Number == CardFunctionNumber::seven)
		{
			return true;
		}
		if (card.card->Number == CardFunctionNumber::bot && card.card->Color == CardFunctionColor::leaf)
		{
			return true;
		}
		return false;
	}
	if (turnsToWait > 0)
	{
		if (card.card->Number == CardFunctionNumber::ace)
		{
			return true;
		}
		return false;
	}
	if (card.card->Color == topDeckCard.Color || card.card->Number == topDeckCard.Number)
	{
		return true;
	}
	else if (card.card->Number == CardFunctionNumber::top)
	{
		return true;
	}
	return false;
}

bool HumanPlayer::tryTakeACard()
{
	for (auto& card : deck->sprites)
	{
		if (isSpriteClicked(card))
		{
			return true;
		}
	}
	return false;
}

bool HumanPlayer::tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed, int cardsToTake, int turnsToWait)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (isSpriteClicked(cards[i].sprite))
		{
			if (canUseThisCard(cards[i], topDeckCard, topHasBeenPlayed, colorToBePlayed, cardsToTake, turnsToWait))
			{
				cardToPlay = move(cards[i].card);
				cards.erase(cards.begin() + i);
				if (cardToPlay->Number == CardFunctionNumber::top)
				{
					(*choosingColor) = true;
				}
				return true;
			}
		}
	}
	return false;
}