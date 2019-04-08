#include <vector>
#include <string>
#include "PokerEvaluator.h"

using namespace std;

PokerEvaluator::PokerEvaluator(vector<Card> cards_in)
{
    if (cards_in.size() != 7)
    {
        throw "Wrong number of cards.";
    }
    cards = cards_in;
}

vector<Card> PokerEvaluator::best_hand_vector()
{
    return vector<Card>();
}

string PokerEvaluator::best_hand()
{
    return "";
}