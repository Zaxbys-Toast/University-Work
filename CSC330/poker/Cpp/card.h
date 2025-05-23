#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
class Card {
	private:
		 char rank, suit;
	
	public:
		Card(char rank, char suit);
		Card(std::string& cardStr);
		char getRank() const;
		
		char getSuit() const;

		int getRankValue() const;

		int getSuitValue() const;

		std::string toString() const;

};

#endif
