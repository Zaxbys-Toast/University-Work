#include <vector>
#include "card.h"

class Deck {
	private:
		std::vector<Card> cards;
	public:
		Deck();
		void shuffle();
		Card deal();
		
};
