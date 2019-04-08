#include <iostream>
using namespace std;

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "Card.h"
#include "Deck.h"

int main()
{
	//cout << "Hello World!!!" << endl;

    Catch::Session().run();

	return 0;
}

TEST_CASE("Test Cards")
{
	SECTION("Test create bad cards")
	{
		Card c1(-10, "Hearts");
		Card c2(10, "Fish");
		Card c3(-10, "Fish");

		REQUIRE(c1.getNumericValue() == 2);
		REQUIRE(c1.getSuit() == "Hearts");
		REQUIRE(c2.getNumericValue() == 10);
		REQUIRE(c2.getSuit() == "Clubs");
		REQUIRE(c3.getNumericValue() == 2);
		REQUIRE(c3.getSuit() == "Clubs");
	}

	SECTION("Test create 52 cards")
	{
		string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
		for (int i = 0; i < 4; i++)
		{
			for (int num = 2; num <= 14; num++)
			{
				Card c(num, suits[i]);
				REQUIRE(c.getNumericValue() == num);
				REQUIRE(c.getSuit() == suits[i]);
			}
		}
	}

	SECTION("Test toString()")
	{
		Card c1(3, "Diamonds");
		Card c2(10, "Hearts");
		Card c3(14, "Spades");

		REQUIRE(c1.toString() == "3 of Diamonds");
		REQUIRE(c2.toString() == "10 of Hearts");
		REQUIRE(c3.toString() == "Ace of Spades");
	}
}

TEST_CASE("Test Deck")
{
    SECTION("Test unique")
    {
        Deck d;

        REQUIRE(d.size() == 52);

        for(int i = 0; i < d.size(); i++)
        {
            for (int j = i+1; j < d.size(); j++)
            {
                REQUIRE(((d[i].getNumericValue() != d[j].getNumericValue())
                    || (d[i].getSuit() != d[j].getSuit())));
            }
        }
    }

	SECTION("Test shuffle")
	{
		bool first_card_different = false;
		bool last_card_different = false;

		for (int i = 0; i < 3; i++)
		{
			Deck d;
			d.shuffle();
			if (d[0].getNumericValue() != 2 || d[0].getSuit() != "Spades")
			{
				first_card_different = true;
			}
			if (d[51].getNumericValue() != 14 || d[51].getSuit() != "Clubs")
			{
				last_card_different = true;
			}
		}
		
		REQUIRE(first_card_different);
		REQUIRE(last_card_different);

		first_card_different = false;
		last_card_different = false;
		Deck reference;
		reference.shuffle();
		for (int i = 0; i < 3; i++)
		{
			Deck d;
			d.shuffle();
			if (d[0].getNumericValue() != reference[0].getNumericValue() || d[0].getSuit() != reference[0].getSuit())
			{
				first_card_different = true;
			}
			if (d[51].getNumericValue() != reference[51].getNumericValue() || d[51].getSuit() != reference[51].getSuit())
			{
				last_card_different = true;
			}
		}

		REQUIRE(first_card_different);
		REQUIRE(last_card_different);

	}

	SECTION("Test deal")
	{
		Deck d;
		vector<Card> deal = d.deal(3);
		REQUIRE(d.size() == 49);
		REQUIRE(deal.size() == 3);
		REQUIRE((deal[0].getNumericValue() == 14 && deal[0].getSuit() == "Clubs"));
		REQUIRE_THROWS(d.deal(50));

		Deck e;
		e.shuffle();
		Card c = e.deal(1)[0];
		for (int i = 0; i < 51; i++)
		{
			REQUIRE((c.getNumericValue() != e[i].getNumericValue() || c.getSuit() != e[i].getSuit()));
		}
	}
}
