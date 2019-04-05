#include <iostream>
using namespace std;

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "Card.h"
#include "Deck.h"

int main()
{
	cout << "Hello World!!!" << endl;

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

TEST_CASE("Test Desk")
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
}
