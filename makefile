OBJS	= main.o Card.o Deck.o PokerEvaluator.o
SOURCE	= main.cpp Card.cpp Deck.cpp PokerEvaluator.cpp
HEADER	= catch.hpp Card.h Deck.h PokerEvaluator.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++17
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Card.o: Card.cpp
	$(CC) $(FLAGS) Card.cpp


clean:
	rm -f $(OBJS) $(OUT)
