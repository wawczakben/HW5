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
            }
            if (better_sorted_hand(candidate, retval))
            {
                retval = candidate;
            }
        }
    }
    return retval;
}

string PokerEvaluator::best_hand()
{
    // return the string representation of each Card in best_hand_vector(),
    // separated by newlines
    string retval = "";
    vector<Card> hand = best_hand_vector();

    for(int i = 0; i < hand.size(); i++)
    {
        retval += hand[i].toString();
        if (i != hand.size()-1)
        {
            retval += "\n";
        }
    }
    return retval;
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
                    && suitToInteger(cards[i].getSuit()) > suitToInteger(cards[i+1].getSuit())))
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

bool PokerEvaluator::isFourOfAKind(vector<Card> hand)
{
    for (int i = 0; i <= 1; i++)
    {
        bool allEqual = true;
        for (int j = i; j < i+3; j++)
        {
            if (hand[j].getNumericValue() != hand[j+1].getNumericValue())
            {
                allEqual = false;
                break;
            }
        }
        if (allEqual)
        {
            return true;
        }
    }
    return false;
}

bool PokerEvaluator::isFullHouse(vector<Card> hand)
{
    if (hand[0].getNumericValue() != hand[1].getNumericValue())
    {
        return false;
    }
    if (hand[3].getNumericValue() != hand[4].getNumericValue())
    {
        return false;
    }
    return ((hand[2].getNumericValue() == hand[1].getNumericValue())
        || (hand[2].getNumericValue() == hand[3].getNumericValue()));
}

bool PokerEvaluator::isThreeOfAKind(vector<Card> hand)
{
    for (int i = 0; i <= 2; i++)
    {
        bool allEqual = true;
        for (int j = i; j < i+2; j++)
        {
            if (hand[j].getNumericValue() != hand[j+1].getNumericValue())
            {
                allEqual = false;
                break;
            }
        }
        if (allEqual)
        {
            return true;
        }
    }
    return false;
}

vector<Card> PokerEvaluator::kickers(vector<Card> hand)
{
    vector<Card> retval;
    for (int i = 0; i < hand.size(); i++)
    {
        if (i > 0 && hand[i].getNumericValue() == hand[i-1].getNumericValue())
        {
            continue;
        }
        if (i < hand.size()-1 && hand[i].getNumericValue() == hand[i+1].getNumericValue())
        {
            continue;
        }
        retval.push_back(hand[i]);
    }
    return retval;
}

bool PokerEvaluator::isPair(vector<Card> hand)
{
    for (int i = 0; i < 4; i++)
    {
        if (hand[i].getNumericValue() == hand[i+1].getNumericValue())
        {
            return true;
        }
    }
    return false;
}

bool PokerEvaluator::isTwoPair(vector<Card> hand)
{
    return (isPair(hand) && kickers(hand).size() == 1);
}

bool PokerEvaluator::better_sorted_hand(vector<Card> better, vector<Card> worse)
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
            return true;
        }
        if (better[0].getNumericValue() > worse[0].getNumericValue()
            || (better[0].getNumericValue() == worse[0].getNumericValue()
                && suitToInteger(better[0].getSuit()) > suitToInteger(worse[0].getSuit())))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (isFourOfAKind(better))
    {
        if (isStraight(worse) && isFlush(worse))
        {
            return false;
        }
        if (!isFourOfAKind(worse))
        {
            return true;
        }
        if (better[1].getNumericValue() > worse[1].getNumericValue())
        {
            return true;
        }
        else if (better[1].getNumericValue() < worse[1].getNumericValue())
        {
            return false;
        }
        Card better_kicker, worse_kicker;
        if (better[0].getNumericValue() == better[1].getNumericValue())
        {
            better_kicker = better[4];
        }
        else
        {
            better_kicker = better[0];
        }
        if (worse[0].getNumericValue() == worse[1].getNumericValue())
        {
            worse_kicker = worse[4];
        }
        else
        {
            worse_kicker = worse[0];
        }
        if (better_kicker.getNumericValue() > worse_kicker.getNumericValue())
        {
            return true;
        }
        else if (better_kicker.getNumericValue() < worse_kicker.getNumericValue())
        {
            return false;
        }
        return (suitToInteger(better_kicker.getSuit()) > suitToInteger(worse_kicker.getSuit()));
    }
    if (isFullHouse(better))
    {
        if (isStraight(worse) && isFlush(worse))
        {
            return false;
        }
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (!isFullHouse(worse))
        {
            return true;
        }
        if (better[2].getNumericValue() > worse[2].getNumericValue())
        {
            return true;
        }
        if (better[2].getNumericValue() < worse[2].getNumericValue())
        {
            return false;
        }
        vector<Card> better_pair, worse_pair;
        if (better[1].getNumericValue() == better[2].getNumericValue())
        {
            better_pair.push_back(better[3]);
            better_pair.push_back(better[4]);
        }
        else
        {
            better_pair.push_back(better[0]);
            better_pair.push_back(better[1]);
        }
        if (worse[1].getNumericValue() == worse[2].getNumericValue())
        {
            worse_pair.push_back(worse[3]);
            worse_pair.push_back(worse[4]);
        }
        else
        {
            worse_pair.push_back(worse[0]);
            worse_pair.push_back(worse[1]);
        }
        if (better_pair[0].getNumericValue() > worse_pair[0].getNumericValue())
        {
            return true;
        }
        else if (better_pair[0].getNumericValue() < worse_pair[0].getNumericValue())
        {
            return false;
        }
        vector<Card> better_triple, worse_triple;
        if (better[1].getNumericValue() == better[2].getNumericValue())
        {
            better_triple.push_back(better[0]);
            better_triple.push_back(better[1]);
            better_triple.push_back(better[2]);
        }
        else
        {
            better_triple.push_back(better[2]);
            better_triple.push_back(better[3]);
            better_triple.push_back(better[4]);
        }
        if (worse[1].getNumericValue() == worse[2].getNumericValue())
        {
            worse_triple.push_back(worse[0]);
            worse_triple.push_back(worse[1]);
            worse_triple.push_back(worse[2]);
        }
        else
        {
            worse_triple.push_back(worse[2]);
            worse_triple.push_back(worse[3]);
            worse_triple.push_back(worse[4]);
        }
        for (int i = 2; i >= 0; i--)
        {
            if (suitToInteger(better_triple[i].getSuit()) > suitToInteger(worse_triple[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better_triple[i].getSuit()) < suitToInteger(worse_triple[i].getSuit()))
            {
                return false;
            }
        }
        for (int i = 1; i >= 0; i--)
        {
            if (suitToInteger(better_pair[i].getSuit()) > suitToInteger(worse_pair[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better_pair[i].getSuit()) < suitToInteger(worse_pair[i].getSuit()))
            {
                return false;
            }
        }
        return false;
    }
    if (isFlush(better))
    {
        // not straight
        if (isStraight(worse) && isFlush(worse))
        {
            return false;
        }
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (isFullHouse(worse))
        {
            return false;
        }
        if (!isFlush(worse))
        {
            return true;
        }
        for (int i = better.size()-1; i >= 0; i--)
        {
            if (better[i].getNumericValue() > worse[i].getNumericValue())
            {
                return true;
            }
            else if (better[i].getNumericValue() < worse[i].getNumericValue())
            {
                return false;
            }
        }
        return (suitToInteger(better[0].getSuit()) > suitToInteger(worse[0].getSuit()));
    }
    if (isStraight(better))
    {
        // not flush
        if (isStraight(worse) && isFlush(worse))
        {
            return false;
        }
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (isFullHouse(worse))
        {
            return false;
        }
        if (isFlush(worse))
        {
            return false;
        }
        if (!isStraight(worse))
        {
            return true;
        }
        if (better[0].getNumericValue() > worse[0].getNumericValue())
        {
            return true;
        }
        else if (better[0].getNumericValue() < worse[0].getNumericValue())
        {
            return false;
        }
        for (int i = better.size()-1; i >= 0; i++)
        {
            if (suitToInteger(better[i].getSuit()) > suitToInteger(worse[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better[i].getSuit()) < suitToInteger(worse[i].getSuit()))
            {
                return false;
            }
        }
        return false;
    }
    if (isThreeOfAKind(better))
    {
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (isFullHouse(worse))
        {
            return false;
        }
        if (isFlush(worse))
        {
            return false;
        }
        if (isStraight(worse))
        {
            return false;
        }
        if (!isThreeOfAKind(worse))
        {
            return true;
        }
        if (better[2].getNumericValue() > worse[2].getNumericValue())
        {
            return true;
        }
        else if (better[2].getNumericValue() < worse[2].getNumericValue())
        {
            return false;
        }
        vector<Card> better_kickers = kickers(better), worse_kickers = kickers(worse);
        for (int i = 1; i >= 0; i--)
        {
            if (better_kickers[i].getNumericValue() > worse_kickers[i].getNumericValue())
            {
                return true;
            }
            else if (better_kickers[i].getNumericValue() < worse_kickers[i].getNumericValue())
            {
                return false;
            }
        }
        if (suitToInteger(better[2].getSuit()) > suitToInteger(better[2].getSuit()))
        {
            return true;
        }
        else if (suitToInteger(better[2].getSuit()) < suitToInteger(better[2].getSuit()))
        {
            return false;
        }
        for (int i = 1; i >= 0; i--)
        {
            if (suitToInteger(better_kickers[i].getSuit()) > suitToInteger(better_kickers[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better_kickers[i].getSuit()) < suitToInteger(better_kickers[i].getSuit()))
            {
                return false;
            }
        }
        return false;
    }
    if (isTwoPair(better))
    {
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (isFullHouse(worse))
        {
            return false;
        }
        if (isFlush(worse))
        {
            return false;
        }
        if (isStraight(worse))
        {
            return false;
        }
        if (isThreeOfAKind(worse))
        {
            return false;
        }
        if (!isTwoPair(worse))
        {
            return true;
        }
        Card better_kicker = kickers(better)[0], worse_kicker = kickers(worse)[0];
        for (int i = 0; i < better.size(); i++)
        {
            if (better[i].getNumericValue() == better_kicker.getNumericValue())
            {
                better.erase(better.begin()+i);
                break;
            }
        }
        for (int i = 0; i < worse.size(); i++)
        {
            if (worse[i].getNumericValue() == worse_kicker.getNumericValue())
            {
                worse.erase(worse.begin()+i);
                break;
            }
        }
        if (better[3].getNumericValue() > worse[3].getNumericValue())
        {
            return true;
        }
        else if (better[3].getNumericValue() < worse[3].getNumericValue())
        {
            return false;
        }
        if (better[0].getNumericValue() > worse[0].getNumericValue())
        {
            return true;
        }
        else if (better[0].getNumericValue() < worse[0].getNumericValue())
        {
            return false;
        }
        if (better_kicker.getNumericValue() > worse_kicker.getNumericValue())
        {
            return true;
        }
        else if (better_kicker.getNumericValue() < worse_kicker.getNumericValue())
        {
            return false;
        }
        for (int i = 3; i >= 0; i--)
        {
            if (suitToInteger(better[i].getSuit()) > suitToInteger(worse[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better[i].getSuit()) < suitToInteger(worse[i].getSuit()))
            {
                return false;
            }
        }
        return (suitToInteger(better_kicker.getSuit()) > suitToInteger(worse_kicker.getSuit()));
    }
    if (isPair(better))
    {
        if (isFourOfAKind(worse))
        {
            return false;
        }
        if (isFullHouse(worse))
        {
            return false;
        }
        if (isFlush(worse))
        {
            return false;
        }
        if (isStraight(worse))
        {
            return false;
        }
        if (isThreeOfAKind(worse))
        {
            return false;
        }
        if (isTwoPair(worse))
        {
            return false;
        }
        if (!isPair(worse))
        {
            return true;
        }
        vector<Card> better_pair, worse_pair;
        for (int i = 0; i < better.size()-1; i++)
        {
            if (better[i].getNumericValue() == better[i+1].getNumericValue())
            {
                better_pair.push_back(better[i]);
                better_pair.push_back(better[i+1]);
            }
        }
        for (int i = 0; i < worse.size()-1; i++)
        {
            if (worse[i].getNumericValue() == worse[i+1].getNumericValue())
            {
                worse_pair.push_back(worse[i]);
                worse_pair.push_back(worse[i+1]);
            }
        }
        if (better_pair[0].getNumericValue() > worse_pair[0].getNumericValue())
        {
            return true;
        }
        else if (better_pair[0].getNumericValue() < worse_pair[0].getNumericValue())
        {
            return false;
        }
        vector<Card> better_kickers = kickers(better), worse_kickers = kickers(worse);
        for (int i = 2; i >= 0; i--)
        {
            if (better_kickers[i].getNumericValue() > worse_kickers[i].getNumericValue())
            {
                return true;
            }
            else if (better_kickers[i].getNumericValue() < worse_kickers[i].getNumericValue())
            {
                return false;
            }
        }
        for (int i = 1; i >= 0; i--)
        {
            if (suitToInteger(better_pair[i].getSuit()) > suitToInteger(worse_pair[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better_pair[i].getSuit()) < suitToInteger(worse_pair[i].getSuit()))
            {
                return false;
            }
        }
        for (int i = 2; i >= 0; i--)
        {
            if (suitToInteger(better_kickers[i].getSuit()) > suitToInteger(worse_kickers[i].getSuit()))
            {
                return true;
            }
            else if (suitToInteger(better_kickers[i].getSuit()) > suitToInteger(worse_kickers[i].getSuit()))
            {
                return false;
            }
        }
        return false;
    }
    // better is a high card
    if (isFourOfAKind(worse))
    {
        return false;
    }
    if (isFullHouse(worse))
    {
        return false;
    }
    if (isFlush(worse))
    {
        return false;
    }
    if (isStraight(worse))
    {
        return false;
    }
    if (isThreeOfAKind(worse))
    {
        return false;
    }
    if (isTwoPair(worse))
    {
        return false;
    }
    if (isPair(worse))
    {
        return false;
    }
    for (int i = 4; i >= 0; i--)
    {
        if (better[i].getNumericValue() > worse[i].getNumericValue())
        {
            return true;
        }
        else if (better[i].getNumericValue() < worse[i].getNumericValue())
        {
            return false;
        }
    }
    for (int i = 4; i >= 0; i--)
    {
        if (suitToInteger(better[i].getSuit()) > suitToInteger(worse[i].getSuit()))
        {
            return true;
        }
        else if (suitToInteger(better[i].getSuit()) < suitToInteger(worse[i].getSuit()))
        {
            return false;
        }
    }
    return false;
}