#include <vector>
#include <algorithm>
#include "Deck.h"

using namespace std;

Deck::Deck()
{
    for(int i = 2; i <= 14; i++)
    {
        Card a(i, "Spades");
        deck.push_back(a);

        Card b(i, "Hearts");
        deck.push_back(b);

        Card c(i, "Diamonds");
        deck.push_back(c);

        Card d(i, "Clubs");
        deck.push_back(d);
    }
}

int Deck::size()
{
    return deck.size();
}

Card Deck::operator [] (int i)
{
    return deck[i];
}

void Deck::shuffle()
{
    random_shuffle(deck.begin(), deck.end());
}

vector<Card> Deck::deal(int num)
{
    vector<Card> retval;
    if (num > deck.size())
    {
        throw "Drew too many cards.";
    }
    for (int i = 0; i < num; i++)
    {
        retval.push_back(deck.back());
        deck.pop_back();
    }
    return retval;
}