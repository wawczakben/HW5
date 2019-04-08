#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"

using namespace std;

class PokerEvaluator
{
public:
    PokerEvaluator(vector<Card> cards_in);
    string best_hand();
private:
    vector<Card> cards;
    vector<Card> best_hand_vector();
};
