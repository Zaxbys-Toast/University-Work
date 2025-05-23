#include "card.h"
#include <vector>
#include <string>

class Player {
    private:
        std::vector<Card> hand;

    public:
	Player();
	std::vector<Card> getHand() const;
        void dealCard(const Card& card);
        void sortByRank();
        void sortBySuit();

        bool isRoyal() const;
        bool isStraightFlush() const;
        bool isFour() const;
        bool isFull() const;
        bool isFlush() const;
        bool isStraight() const;
        bool isThree() const;
        bool isTwo() const;
        bool isPair() const;

        int handRank() const;
        void printHand();
};

