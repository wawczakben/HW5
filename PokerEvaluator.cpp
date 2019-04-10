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
    sortHand();
}

vector<Card> PokerEvaluator::best_hand_vector()
{
    vector<Card> retval;
    for (int skip1 = 0; skip1 < 6; skip1++)
    {
        for (int skip2 = skip1+1; skip2 < 7; skip2++)
        {
            vector<Card> candidate;
            for (int i = 0; i < 7; i++)
            {
                if (i != skip1 && i != skip2)
                {
                    candidate.push_back(cards[i]);
                }
                if (better_hand(candidate, retval))
                {
                    retval = candidate;
                }
            }
        }
    }
    return retval;
}

string PokerEvaluator::best_hand()
{
    // return the string representation of each Card in best_hand_vector(),
    // separated by newlines
    return "";
}

void PokerEvaluator::sortHand()
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true; // change to false if a swap is made
        for(int i = 0; i < cards.size()-1; i++)
        {
            if(cards[i].getNumericValue() > cards[i+1].getNumericValue()
                || (cards[i].getNumericValue() == cards[i+1].getNumericValue()
                    && suitToInteger(cards[i].getSuit()) > suitToInteger(cards[i+1].getSuit)))
            {
                swap(cards[i], cards[i+1]);
                sorted = false;
            }
        }
    }
}

int PokerEvaluator::suitToInteger(string s)
{
    if (s == "Clubs")
    {
        return 1;
    }
    if (s == "Diamonds")
    {
        return 2;
    }
    if (s == "Hearts")
    {
        return 3;
    }
    if (s == "Spades")
    {
        return 4;
    }
    return 0;
}

bool PokerEvaluator::isStraight(vector<Card> hand)
{
    for(int i = 0; i < hand.size() - 1; i++)
    {
        if(hand[i].getNumericValue() != hand[i + 1].getNumericValue() - 1)
        {
            return false;
        }
    }
    return true;
}

bool PokerEvaluator::isFlush(vector<Card> hand)
{
    for(int i = 0; i < hand.size() - 1; i++)
    {
        if(hand[i].getSuit() != hand[i + 1].getSuit())
        {
            return false;
        }
    }
    return true;
}

bool PokerEvaluator::better_hand(vector<Card> better, vector<Card> worse)
{
    if (worse.size() == 0)
    {
        // initializing retval in best_hand()
        return true;
    }
    if (isStraight(better) && isFlush(better))
    {
        // straight flush
        if (!isStraight(worse) || !isFlush(worse))
        {
            return false;
        }
        if (better[0].getNumericValue() > worse[0].getNumericValue()
            || (better[0].getNumericValue() == worse[0].getNumericValue()
                && suitToInteger(better[0].getSuit()) > suitToInteger(worse[0].getSuit())))
        {
            return true;
        }
    }

}