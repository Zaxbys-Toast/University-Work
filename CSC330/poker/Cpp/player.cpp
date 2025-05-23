#include "player.h"
#include <algorithm>
#include <iostream>

using namespace std;
Player::Player() {

}
std::vector<Card> Player::getHand() const{
	return hand;
}
void Player::dealCard(const Card& card) {
    if (hand.size() < 5) {
        hand.push_back(card);
    }
}

void Player::sortByRank() {
    sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
        return a.getRankValue() > b.getRankValue();
    });
}

void Player::sortBySuit() {
    sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
        return a.getSuitValue() > b.getSuitValue();
    });
}

bool Player::isRoyal() const{
    return isFlush() && isStraight() && hand.back().getRank() == 'T';
}

bool Player::isStraightFlush() const {
    return isFlush() && isStraight();
}

bool Player::isFour() const {
    return (hand[0].getRank() == hand[1].getRank() &&
            hand[1].getRank() == hand[2].getRank() &&
            hand[2].getRank() == hand[3].getRank()) ||
           (hand[1].getRank() == hand[2].getRank() &&
            hand[2].getRank() == hand[3].getRank() &&
            hand[3].getRank() == hand[4].getRank());
}

bool Player::isFull() const{
    return (hand[0].getRank() == hand[1].getRank() &&
            hand[1].getRank() == hand[2].getRank() &&
            hand[3].getRank() == hand[4].getRank()) ||
           (hand[2].getRank() == hand[3].getRank() &&
            hand[3].getRank() == hand[4].getRank() &&
            hand[0].getRank() == hand[1].getRank());
}

bool Player::isFlush() const{
    return hand[0].getSuit() == hand[1].getSuit() &&
           hand[1].getSuit() == hand[2].getSuit() &&
           hand[2].getSuit() == hand[3].getSuit() &&
           hand[3].getSuit() == hand[4].getSuit();
}

bool Player::isStraight() const{
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRankValue() - 1 != hand[i + 1].getRankValue()) {
            return false;
        }
    }
    return true;
}

bool Player::isThree() const{
    return (hand[0].getRank() == hand[1].getRank() &&
            hand[1].getRank() == hand[2].getRank()) ||
           (hand[1].getRank() == hand[2].getRank() &&
            hand[2].getRank() == hand[3].getRank()) ||
           (hand[2].getRank() == hand[3].getRank() &&
            hand[3].getRank() == hand[4].getRank());
}

bool Player::isTwo() const{
    return (hand[0].getRank() == hand[1].getRank() &&
            hand[2].getRank() == hand[3].getRank()) ||
           (hand[1].getRank() == hand[2].getRank() &&
            hand[3].getRank() == hand[4].getRank());
}

bool Player::isPair() const{
    return hand[0].getRank() == hand[1].getRank() ||
           hand[1].getRank() == hand[2].getRank() ||
           hand[2].getRank() == hand[3].getRank() ||
           hand[3].getRank() == hand[4].getRank();
}

int Player::handRank() const{
    if (isRoyal()) return 10;
    if (isStraightFlush()) return 9;
    if (isFour()) return 8;
    if (isFull()) return 7;
    if (isFlush()) return 6;
    if (isStraight()) return 5;
    if (isThree()) return 4;
    if (isTwo()) return 3;
    if (isPair()) return 2;
    return 1;
}

void Player::printHand() {
    for (const Card& card : hand) {
        cout << card.toString() << " ";
    }
    cout << endl;
}

