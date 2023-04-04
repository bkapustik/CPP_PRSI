#include "Deck.h"

shared_ptr<Sprite> Deck::createBackSprite(int shift)
{
	auto newSprite = make_shared<Sprite>(Sprite((*graphics->backCardSideTexture)));

	graphics->scaleCardSize(newSprite);
	graphics->setPositionRelativeToCardSize(newSprite, PositionOfFirstCard.x + 10 * shift, PositionOfFirstCard.y);

	return newSprite;
}

void Deck::changeShownCard()
{
	frontDeckCard = make_shared<Sprite>(Sprite((*showTopCard()->Texture)));
	graphics->scaleCardSize(frontDeckCard);
	graphics->setPositionRelativeToCardSize(frontDeckCard, graphics->ScreenWidth / 2, graphics->ScreenHeight / 2);
}

Deck::Deck(vector<shared_ptr<Card>>& cards, std::shared_ptr<GraphicsHelper> graphics)
{
	this->PositionOfFirstCard = Vector2f(graphics->ScreenWidth/2 + 200, graphics->ScreenHeight/2);
	this->graphics = graphics;
	sprites = vector<shared_ptr<Sprite>>();
	shuffle(cards);

	for (int i = 0;i < cards.size()-1; i++)
	{
		Cards.push(cards[i]);

		auto newSprite = createBackSprite(i);
		sprites.push_back(newSprite);
	}

	changeShownCard();
}

void Deck::shuffle(vector<shared_ptr<Card>>& cards)
{
	srand(time(0));
	random_shuffle(cards.begin(), cards.end());
}

void Deck::shuffle()
{
	auto cards = cardsToVector();
	shuffle(cards);
	vectorToQueue(cards);
}

vector<shared_ptr<Card>> Deck::cardsToVector()
{
	vector<shared_ptr<Card>> cards = vector<shared_ptr<Card>>();

	while (Cards.size() > 0)
	{
		auto card = Cards.front();
		cards.push_back(card);
		Cards.pop();
	}

	return cards;
}

void Deck::vectorToQueue(vector<shared_ptr<Card>>& cards)
{
	for (auto card : cards)
	{
		Cards.push(card);
	}
}

void Deck::print()
{
	auto newQueue = queue<shared_ptr<Card>>();

	while (Cards.size() > 0)
	{
		auto card = Cards.front();
		newQueue.push(card);
		Cards.pop();

		cout << Opener::colorToName(card->Color) << ' ' << Opener::numberToName(card->Number) << endl;
	}

	Cards = newQueue;
}

shared_ptr<Card> Deck::deque()
{
	auto card = Cards.front();
	Cards.pop();
	return card;
}

vector<shared_ptr<Card>> Deck::getNCards(int n)
{
	vector<shared_ptr<Card>> cards = vector<shared_ptr<Card>>();

	//can not start with card at start of deck
	for (int i = 0; i < n; i++)
	{
		if (Cards.size() > 1)
		{
			auto card = deque();
			cards.push_back(card);
			sprites.erase(sprites.begin());
		}
	}
	return cards;
}

void Deck::addACard(shared_ptr<Card> card)
{
	Cards.push(card);
	auto newSprite = createBackSprite(sprites.size()-1);
	sprites.push_back(newSprite);
	changeShownCard();
}

shared_ptr<Card> Deck::showTopCard() const
{
	return Cards.back();
}
