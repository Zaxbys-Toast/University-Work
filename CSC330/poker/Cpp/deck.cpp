#include "deck.h"
#include <algorithm>
#include <random>

Deck::Deck()
{
	char ranks[] = "23456789TJQKA";
	char suits[] = "HDSC";

	for ( char suit : suits )
	{
		for ( char rank : ranks )
		{
			cards.emplace_back(rank, suit);
		}
	}
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::deal()
{
	Card card = cards.back();
	cards.pop_back();
	
	return card;
}


