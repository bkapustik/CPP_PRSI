#include "Player.h"

Player::Player(Vector2f positionOfFirstCard, shared_ptr<GraphicsHelper> graphics)
{
	isOnTurn = false;
	hasFinished = false;
	PositionOfFirstCard = positionOfFirstCard;
	this->graphics = graphics;
	cards = vector<CardSprite>();
}

void Player::takeCards(vector<shared_ptr<Card>>& cards)
{
	for (auto card : cards)
	{
		CardSprite cardSprite = CardSprite(card, make_shared<Sprite>((*graphics->backCardSideTexture)));
		graphics->scaleCardSize(cardSprite.sprite);
		graphics->setPositionRelativeToCardSize(cardSprite.sprite, PositionOfFirstCard.x + this->cards.size()*30, PositionOfFirstCard.y);
		this->cards.push_back(cardSprite);
	}
}

void Player::setOnTurn()
{
	isOnTurn = true;
}

void Player::cancelIsOnTurn()
{
	isOnTurn = false;
}

bool Player::tryCanCancelTakingACard(shared_ptr<Card>& cancellingCard, shared_ptr<Card> topDeckCard)
{
	if (tryReturnCardOfNumber(CardFunctionNumber::seven, cancellingCard))
	{
		return true;
	}
	if (tryReturnCardOfColorAndNumber(CardFunctionColor::leaf, CardFunctionNumber::bot, cancellingCard))
	{
		return true;
	}
	return false;
}

bool Player::tryCanCancelBeingSkipped(shared_ptr<Card>& cancellingCard, shared_ptr<Card> topDeckCard)
{
	if (tryReturnCardOfNumber(CardFunctionNumber::ace, cancellingCard))
	{
		return true;
	}
	return false;
}

CardFunctionColor Player::getRandomColor()
{
	const int numberOfColors = 4;
	CardFunctionColor colors [numberOfColors] = { CardFunctionColor::leaf, CardFunctionColor::bell, CardFunctionColor::heart, CardFunctionColor::acorn };
	int randomNumber = Helper::randomInRange(numberOfColors);
	return (colors[randomNumber]);
}

bool Player::tryPlayACard(shared_ptr<Card>& cardToPlay, shared_ptr<Card> topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed)
{
	CardFunctionColor colorToPlay = topDeckCard->Color;

	if ((*topHasBeenPlayed))
	{
		colorToPlay = (*colorToBePlayed);
	}

	if (tryReturnCardOfColorAndNumber(topDeckCard->Color, CardFunctionNumber::seven, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfColorAndNumber(topDeckCard->Color, CardFunctionNumber::ace, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfNumber(CardFunctionNumber::top, cardToPlay))
	{
		colorToBePlayed = make_shared<CardFunctionColor>(getRandomColor());
		return true;
	}

	if (tryReturnCardOfColor(colorToPlay, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfNumber(topDeckCard->Number, cardToPlay))
	{
		return true;
	}

	return false;
}

bool Player::tryReturnCardOfColor(CardFunctionColor color, shared_ptr<Card>& cardToReturn)
{
	for (auto card : cards)
	{
		if (card.card->Color == color)
		{
			cardToReturn = card.card;
			return true;
		}
	}
	return false;
}

bool Player::tryReturnCardOfNumber(CardFunctionNumber number, shared_ptr<Card>& cardToReturn)
{
	for (auto card : cards)
	{
		if (card.card->Number == number)
		{
			cardToReturn = card.card;
			return true;
		}
	}
	return false;
}

bool Player::tryReturnCardOfColorAndNumber(CardFunctionColor color, CardFunctionNumber number, shared_ptr<Card>& cardToReturn)
{
	for (auto card : cards)
	{
		if (card.card->Number == number && card.card->Color == color)
		{
			cardToReturn = card.card;
			return true;
		}
	}
	return false;
}

void Player::removeCard(shared_ptr<Card> cardToRemove)
{
	vector<CardSprite> newHand = vector<CardSprite>();

	for (int i = 0; i < cards.size(); i++)
	{
		if (cardToRemove->Color != cards[i].card->Color || cardToRemove->Number != cards[i].card->Number)
		{
			graphics->setPositionRelativeToCardSize(cards[i].sprite, PositionOfFirstCard.x + i * 20, PositionOfFirstCard.y);
			newHand.push_back(cards[i]);
		}
	}
	cards = newHand;
	if (cards.empty())
	{
		hasFinished = true;
	}
}