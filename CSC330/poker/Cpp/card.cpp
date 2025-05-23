#include "card.h"
#include <iostream>
Card::Card(char rank, char suit)
{
	this->rank = rank;
	this->suit = suit;
}

Card::Card(std::string& cardStr)
{
	if  (cardStr.size() == 3 && cardStr.substr(0, 2) == "10") {
        	rank = 'T'; 
		suit = cardStr[2];
	} else if (cardStr.size() == 2 ) {
		rank = cardStr[0];
		suit = cardStr[1];
	} else {
		throw std::invalid_argument("Invalid card string format");
	}
}
char Card::getRank() const
{
	return rank;
}

char Card::getSuit () const
{
	return suit;
}

int Card::getRankValue() const
{
	std::string order = "23456789TJQKA";
	return order.find(rank);	
}

int Card::getSuitValue() const
{
	std::string order = "DCHS";
	return order.find(suit);
}

std::string Card::toString() const
{
	return std::string(1, rank) + suit;
}

