#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "deck.h"
#include "player.h"

using namespace std;

vector<Player> readHandsFromFile(const string& filename) {
    ifstream file(filename);
    vector<Player> players;
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Player player;
        string cardStr;
        while (getline(ss, cardStr, ',')) {
            cardStr.erase(remove(cardStr.begin(), cardStr.end(), ' '), cardStr.end());
            Card card(cardStr);
            player.dealCard(card);
        }
        players.push_back(player);
    }
    file.close();
    return players;
}

bool comparePlayers(const Player& p1, const Player& p2) {
    if (p1.handRank() == p2.handRank()) {
        // If hands have the same rank, sort by individual card rank and suit
        vector<Card> hand1 = p1.getHand();
        vector<Card> hand2 = p2.getHand();

        for (size_t i = 0; i < hand1.size(); ++i) {
            if (hand1[i].getRankValue() != hand2[i].getRankValue()) {
                return hand1[i].getRankValue() > hand2[i].getRankValue();
            }
            // If ranks are equal, compare suits in Spades, Hearts, Clubs, Diamonds order
            if (hand1[i].getSuitValue() != hand2[i].getSuitValue()) {
                return hand1[i].getSuitValue() < hand2[i].getSuitValue();
            }
        }
        return false; // If all cards are equal
    }
    return p1.handRank() > p2.handRank();
}




int main(int argc, char* argv[]) {
    vector<Player> players;

    if (argc == 2) {
        players = readHandsFromFile(argv[1]);
    } else {
        Deck deck;
        deck.shuffle();
        for (int i = 0; i < 6; ++i) {
            Player player;
            for (int j = 0; j < 5; ++j) {
                player.dealCard(deck.deal());
            }
            players.push_back(player);
        }
    }

    for (Player& player : players) {
        player.sortByRank();
    }

    sort(players.begin(), players.end(), comparePlayers);

    for (size_t i = 0; i < players.size(); ++i) {
        cout << "Player " << i + 1 << "'s hand: ";
        players[i].printHand();
        cout << " - Hand Rank: " << players[i].handRank() << " (";
        switch (players[i].handRank()) {
            case 1: cout << "High Card"; break;
            case 2: cout << "One Pair"; break;
            case 3: cout << "Two Pair"; break;
            case 4: cout << "Three of a Kind"; break;
            case 5: cout << "Straight"; break;
            case 6: cout << "Flush"; break;
            case 7: cout << "Full House"; break;
            case 8: cout << "Four of a Kind"; break;
            case 9: cout << "Straight Flush"; break;
        }
        cout << ")" << endl;
    }

    return 0;
}

