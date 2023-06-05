#include <cassert>
#include "GameMenu.h"

using namespace std;

class TestBase
{
public:
    Opener opener = Opener();
    GraphicsHelper graphics;
    GameManager gameManager;
    GameMenuDto menu = GameMenuDto();

    TestBase()
    {
        auto cards = opener.getCards();
        graphics = GraphicsHelper(2, 2, 200, 100, (*cards[0]), opener.getCardBackSide());
        menu.graphics = graphics;
        menu.deck = Deck(cards, graphics);
    }

    void resetDeck()
    {
        auto cards = opener.getCards();
        menu.deck = Deck(cards, graphics);
    }

    void virtual execute()
    {

    }
};

class DeckTests : public TestBase
{
    public:
    DeckTests() : TestBase()
    {
        
    }

    void getCards()
    {
        resetDeck();

        auto cards = menu.deck.getNCards(5);

        assert(cards.size() == 5);
    }

    void cardsCountInDeck()
    {
        resetDeck();

        vector<unique_ptr<Card>> cards = menu.deck.getNCards(31);

        assert(menu.deck.frontDeckCard != nullptr);

        assert(cards.size() == 31);
        cards = menu.deck.getNCards(1);
        assert(cards.size() == 0);
    }

    void addACard()
    {
        resetDeck();

        auto cards = menu.deck.getNCards(32);
        menu.deck.addACard(move(cards[0]), menu.graphics);

        auto card = move(menu.deck.getNCards(1));
        assert(card.size() == 1);
    }

    void execute() override
    {
        getCards();
        cardsCountInDeck();
        addACard();
    }
};

class PlayerTests : public TestBase
{
    public:
    Player player;
    ComputerPlayer pcPlayer;
    HumanPlayer humanPlayer;
    vector<unique_ptr<Card>> playerCards;
    
    PlayerTests() : TestBase()
    {
        reset();
    }

    void reset()
    {
        resetDeck();
        player = Player();
        pcPlayer = ComputerPlayer();
        humanPlayer = HumanPlayer();
        player.cards = vector<CardSprite>();
    }

    void takeCards()
    {
        reset();

        auto card = menu.deck.getNCards(2);

        player.takeCards(card, graphics);

        assert(player.cards.size() == 2);
    }

    void cehckPlayerCards()
    {
        reset();
        assert(player.hasFinished == false);
        player.checkPlayersCards(graphics);
        assert(player.hasFinished == true);
    }

    void returnCardOfColorAndNumber()
    {
        reset();

        auto cardToPlay = make_unique<Card>();
        auto topDeckCard = ColorNumber(CardFunctionColor::acorn, CardFunctionNumber::seven);
        bool topHasBeenPlayed = false;
        auto colorToBePlayed = make_shared<CardFunctionColor>();

        playerCards.push_back(make_unique<Card>(CardFunctionNumber::seven,CardFunctionColor::acorn,make_unique<Texture>()));
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::seven,CardFunctionColor::heart,make_unique<Texture>()));

        player.takeCards(playerCards, graphics);
        player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(cardToPlay->Color == CardFunctionColor::acorn);
        assert(cardToPlay->Number == CardFunctionNumber::seven);
    }

    void returnCardOfCOlor()
    {
        reset();

        auto cardToPlay = make_unique<Card>();
        auto topDeckCard = ColorNumber(CardFunctionColor::heart, CardFunctionNumber::nine);
        bool topHasBeenPlayed = false;
        auto colorToBePlayed = make_shared<CardFunctionColor>();

        playerCards = vector<unique_ptr<Card>>();
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::eight,CardFunctionColor::acorn,make_unique<Texture>()));
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::eight,CardFunctionColor::heart,make_unique<Texture>()));

        player.takeCards(playerCards, graphics);
        player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(cardToPlay->Color == CardFunctionColor::heart);
    }

    void returnCardOfNumber()
    {
        reset();

        auto cardToPlay = make_unique<Card>();
        auto topDeckCard = ColorNumber(CardFunctionColor::heart, CardFunctionNumber::nine);
        bool topHasBeenPlayed = false;
        auto colorToBePlayed = make_shared<CardFunctionColor>();

        playerCards = vector<unique_ptr<Card>>();
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::nine,CardFunctionColor::acorn,make_unique<Texture>()));
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::eight,CardFunctionColor::acorn,make_unique<Texture>()));

        player.takeCards(playerCards, graphics);
        player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(cardToPlay->Number == CardFunctionNumber::nine);
    }

    void wantsCustomTurn()
    {
        assert(player.wantsCustomTurn() == false);
        assert(pcPlayer.wantsCustomTurn() == false);
        assert(humanPlayer.wantsCustomTurn() == true);
    }

    void aiBasicOrderOfCardPriority()
    {
        reset();

        auto cardToPlay = make_unique<Card>();
        auto topDeckCard = ColorNumber(CardFunctionColor::acorn, CardFunctionNumber::nine);
        bool topHasBeenPlayed = false;
        auto colorToBePlayed = make_shared<CardFunctionColor>();

        playerCards = vector<unique_ptr<Card>>();
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::nine,CardFunctionColor::acorn,make_unique<Texture>()));

        playerCards.push_back(make_unique<Card>(CardFunctionNumber::seven,CardFunctionColor::acorn,make_unique<Texture>()));

        playerCards.push_back(make_unique<Card>(CardFunctionNumber::ace,CardFunctionColor::acorn,make_unique<Texture>()));

        playerCards.push_back(make_unique<Card>(CardFunctionNumber::top,CardFunctionColor::leaf,make_unique<Texture>()));

        player.takeCards(playerCards, graphics);
        bool played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);
        
        assert(cardToPlay->Color == CardFunctionColor::acorn && cardToPlay->Number == CardFunctionNumber::seven);
        assert(played == true);

        topDeckCard.Color = CardFunctionColor::acorn;

        colorToBePlayed = make_shared<CardFunctionColor>();

        played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(cardToPlay->Color == CardFunctionColor::acorn && cardToPlay->Number == CardFunctionNumber::ace);
        assert(played == true);
        
        colorToBePlayed = make_shared<CardFunctionColor>();

        played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);
    
        assert(cardToPlay->Color == CardFunctionColor::acorn && cardToPlay->Number == CardFunctionNumber::nine);
        assert(played == true);

        played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(cardToPlay->Color == CardFunctionColor::leaf && cardToPlay->Number == CardFunctionNumber::top);
        assert(played == true);

        played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);
        assert(played == false);    
    }

    void aiTopHasBeenPlayed()
    {
        reset();
        auto cardToPlay = make_unique<Card>();
        auto topDeckCard = ColorNumber(CardFunctionColor::acorn, CardFunctionNumber::bot);
        auto topHasBeenPlayed = true;
        auto colorToBePlayed = make_shared<CardFunctionColor>(CardFunctionColor::bell);
        playerCards = vector<unique_ptr<Card>>();
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::nine, CardFunctionColor::acorn, make_unique<Texture>())); 
        playerCards.push_back(make_unique<Card>(CardFunctionNumber::ace, CardFunctionColor::bell, make_unique<Texture>()));

        player.takeCards(playerCards, menu.graphics);
        bool played = player.tryPlayACard(cardToPlay, topDeckCard, topHasBeenPlayed, colorToBePlayed);

        assert(played == true);
        assert(cardToPlay->Color == CardFunctionColor::bell);
        assert(cardToPlay->Number == CardFunctionNumber::ace);
    }

    void execute() override
    {
        takeCards();   
        cehckPlayerCards();
        returnCardOfColorAndNumber();
        returnCardOfCOlor();
        returnCardOfNumber();
        aiBasicOrderOfCardPriority();
        aiTopHasBeenPlayed();
    }

};

