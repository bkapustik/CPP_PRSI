#include "Player.h"

Player::Player(const Vector2f positionOfFirstCard, GraphicsHelper & graphics)
{
	isOnTurn = false;
	hasFinished = false;
	PositionOfFirstCard = positionOfFirstCard;
	cards = vector<CardSprite>();
}

void Player::takeCards(vector<unique_ptr<Card>>& cards, GraphicsHelper & graphics)
{
	for (int i = 0; i < this->cards.size(); i++)
	{
		graphics.setPositionRelativeToCardSize(this->cards[i].sprite, PositionOfFirstCard.x + i * 30, PositionOfFirstCard.y);
	}
	for (auto& card : cards)
	{
		CardSprite cardSprite = CardSprite(move(card));
		graphics.scaleCardSize(cardSprite.sprite);
		graphics.setPositionRelativeToCardSize(cardSprite.sprite, PositionOfFirstCard.x + this->cards.size() * 30, PositionOfFirstCard.y);
		this->cards.push_back(move(cardSprite));
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

bool Player::tryCanCancelTakingACard(unique_ptr<Card>& cancellingCard)
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

bool Player::tryCanCancelBeingSkipped(unique_ptr<Card>& cancellingCard)
{
	if (tryReturnCardOfNumber(CardFunctionNumber::ace, cancellingCard))
	{
		return true;
	}
	return false;
}

CardFunctionColor Player::getRandomColor() const
{
	const int numberOfColors = 4;
	CardFunctionColor colors[numberOfColors] = { CardFunctionColor::leaf, CardFunctionColor::bell, CardFunctionColor::heart, CardFunctionColor::acorn };
	int randomNumber = Helper::randomInRange(numberOfColors);
	return (colors[randomNumber]);
}

bool Player::tryPlayACard(unique_ptr<Card>& cardToPlay, const ColorNumber& topDeckCard, shared_ptr<bool>& topHasBeenPlayed, shared_ptr<CardFunctionColor>& colorToBePlayed)
{
	CardFunctionColor colorToPlay = topDeckCard.Color;

	if ((*topHasBeenPlayed))
	{
		if (colorToBePlayed)
		{
			colorToPlay = (*colorToBePlayed);
		}
	}

	if (tryReturnCardOfColorAndNumber(topDeckCard.Color, CardFunctionNumber::seven, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfColorAndNumber(topDeckCard.Color, CardFunctionNumber::ace, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfColor(colorToPlay, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfNumber(topDeckCard.Number, cardToPlay))
	{
		return true;
	}

	if (tryReturnCardOfNumber(CardFunctionNumber::top, cardToPlay))
	{
		(*colorToBePlayed) = getRandomColor();
		return true;
	}

	return false;
}

bool Player::tryReturnCardOfColor(const CardFunctionColor color, unique_ptr<Card>& cardToReturn)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (cards[i].card->Color == color)
		{
			cardToReturn = move(cards[i].card);
			cards.erase(cards.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::tryReturnCardOfNumber(const CardFunctionNumber number, unique_ptr<Card>& cardToReturn)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (cards[i].card->Number == number)
		{
			cardToReturn = move(cards[i].card);
			cards.erase(cards.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::tryReturnCardOfColorAndNumber(const CardFunctionColor& color,const CardFunctionNumber& number, unique_ptr<Card>& cardToReturn)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (cards[i].card->Number == number && cards[i].card->Color == color)
		{
			cardToReturn = move(cards[i].card);
			cards.erase(cards.begin() + i);
			return true;
		}
	}
	return false;
}

void Player::checkPlayersCards(GraphicsHelper & graphics)
{
	for (int i = 0; i < cards.size(); i++)
	{
		graphics.setPositionRelativeToCardSize(cards[i].sprite, PositionOfFirstCard.x + i * 20, PositionOfFirstCard.y);
	}
	if (cards.empty())
	{
		hasFinished = true;
	}
}