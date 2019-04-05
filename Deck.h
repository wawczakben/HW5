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


private:
    vector<Card> deck;

};
