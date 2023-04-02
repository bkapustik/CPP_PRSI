#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics, shared_ptr<Deck> deck) : Player(positionOfFirstCard, graphics)
{
	this->deck = deck;
}

void HumanPlayer::takeCards(vector<shared_ptr<Card>>& cards)
{
	for (auto card : cards)
	{
		CardSprite cardSprite = CardSprite(card, make_shared<Sprite>((*card->Texture)));
		graphics->scaleCardSize(cardSprite.sprite);
		graphics->setPositionRelativeToCardSize(cardSprite.sprite, PositionOfFirstCard.x + this->cards.size() * 100, PositionOfFirstCard.y);
		this->cards.push_back(cardSprite);
	}
}

void HumanPlayer::removeCard(shared_ptr<Card> cardToRemove)
{
	vector<CardSprite> newHand = vector<CardSprite>();

	for (int i = 0; i < cards.size(); i++)
	{
		if (cardToRemove->Color != cards[i].card->Color || cardToRemove->Number != cards[i].card->Number)
		{
			graphics->setPositionRelativeToCardSize(cards[i].sprite, PositionOfFirstCard.x + i * 100, PositionOfFirstCard.y);
			newHand.push_back(cards[i]);
		}
	}
	cards = newHand;
	if (cards.empty())
	{
		hasFinished = true;
	}
}

bool HumanPlayer::isSpriteClicked(shared_ptr<Sprite> sprite)
{
	//cout << "this is mouse " << Mouse::getPosition().x << endl;
	//cout << "this is sprite " << sprite->getPosition().x << " this is size " << sprite->getScale().x << endl;

	if (Mouse::getPosition().x > sprite->getPosition().x
		&& Mouse::getPosition().x < sprite->getPosition().x + graphics->CardWidth
		&& Mouse::getPosition().y > sprite->getPosition().y
		&& Mouse::getPosition().y < sprite->getPosition().y + graphics->CardHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HumanPlayer::wantsCustomTurn()
{
	return true;
}

bool HumanPlayer::canUseThisCard(shared_ptr<CardSprite> card, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor> colorToBePlayed, int cardsToTake, int turnsToWait)
{
	if ((*topHasBeenPlayed))
	{
		if (card->card->Color == (*colorToBePlayed))
		{
			return true;
		}
		return false;
	}
	if (cardsToTake > 0)
	{
		if (card->card->Number == CardFunctionNumber::seven)
		{
			return true;
		}
		if (card->card->Number == CardFunctionNumber::bot && card->card->Color == CardFunctionColor::leaf)
		{
			return true;
		}
		return false;
	}
	if (turnsToWait > 0)
	{
		if (card->card->Number == CardFunctionNumber::ace)
		{
			return true;
		}
		return false;
	}
	if (card->card->Color == topDeckCard->Color || card->card->Number == topDeckCard->Number)
	{
		return true;
	}
	else if (card->card->Number == CardFunctionNumber::top)
	{
		return true;
	}
	return false;
}

bool HumanPlayer::tryTakeACard()
{
	for (auto card : deck->sprites)
	{
		if (isSpriteClicked(card))
		{
			return true;
		}
	}
	return false;
}

bool HumanPlayer::tryPlayACard(shared_ptr<Card>& cardToPlay, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor> colorToBePlayed, int cardsToTake, int turnsToWait)
{
	for (auto card : cards)
	{
		if (isSpriteClicked(card.sprite))
		{
			if (canUseThisCard(make_shared<CardSprite>(card), topDeckCard, topHasBeenPlayed, colorToBePlayed, cardsToTake, turnsToWait))
			{
				cardToPlay = card.card;
				return true;
			}
		}
	}
	return false;
}