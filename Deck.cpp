#include "Deck.h"

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
