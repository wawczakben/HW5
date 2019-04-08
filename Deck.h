#pragma once
#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
public:
    Deck();
    int size();
    Card operator[](int i);
    void shuffle();
    vector<Card> deal(int numOfCards);


private:
    vector<Card> deck;

};
