# Five Card Stud - Python
# John King
# CSC330
# 8/27/2024
import sys
from card import Card
from deck import Deck
from collections import Counter

def main():
    # Initialize player hands and table
    table = [[] for _ in range(6)]
    if len(sys.argv) == 2:
        filename = sys.argv[1]
        readHands(filename, table)
    else:
    # Set up the deck and shuffle it
        deck = Deck()
        deck.shuffle()
        deck.printDeck()

    # Deal 5 cards to each player
        deal(deck, table)

    # Print each player's hand
    printHands(table)

    # Evaluate and rank each player's hand
    playerRanks = []
    for i, player in enumerate(table):
        handRank, handType, sortedHand = rankHand(player)
        playerRanks.append((i + 1, handRank, handType, sortedHand))

    # Sort players by hand rank and resolve ties
    playerRanks.sort(key=lambda x: (x[1], tieBreaker(x[3], x[3], x[2])), reverse=True)

    # Print the sorted hands
    printPlayerRanks(playerRanks)
 
def readHands(filename, table):
    with open(filename, 'r') as file:
        lines = file.readlines()

    for i, line in enumerate(lines):
        cards = line.strip().split(', ')
        playerHand = []
        for cardStr in cards:
            cardStr = cardStr.strip()
            if len(cardStr) == 3:  # Handles '10S' format
                rank = cardStr[:2]
                suit = cardStr[2].upper()
            else:  # Handles '9D' format
                rank = cardStr[0]
                suit = cardStr[1].upper()
            
            playerHand.append(Card(suit, rank))
        
        # Make sure we do not exceed the length of the table
        if i < len(table):
            table[i] = playerHand
   
# Deals 5 cards to each player in a circle 
def deal(deck, table):
    for i in range(5):
        for j in range (6):
            table[j].append(deck.dealCard())
# Prints each hand 
def printHands(table):
    print("")
    for i in range(6):
        print(f"---------------")
        for j in range(5):
            table[i][j].printCard()
        print("\n---------------")   


def checkFlush(player):
    suits = [(card.suit) for card in player]
    return len(set(suits)) == 1

def checkStraight(player):
    ranks = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
    rank_values = [ranks.index(card.rank) for card in player]
    rank_values.sort()
    
    if rank_values == [0,1,2,3,12]:
        return True
    
    for i in range(4):
        if rank_values[i+1] - rank_values[i] != 1:
            return False
    return True

def countRank(player):
    ranks = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
    rankValues = [ranks.index(card.rank) for card in player]
    rankCount = Counter(rankValues)
    
    return sorted(rankCount.values(), reverse=True)

def rankValues(card):
    # Returns the rank value of a single card
    ranks = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
    return (ranks.index(card.rank))

    return (ranks.index(card.rank))

def checkFour(count):
    return count == [4,1]

def checkFullHouse(count):
    return count == [3,2]

def checkThree(count):
    return count == [3,1,1]

def checkTwoPair(count):
    return count == [2,2,1]

def checkPair(count):
    return count == [2,1,1,1]

def rankHand(player):
    sortedHand = sorted(player, key=lambda card: rankValues(card), reverse=True)
    counts = countRank(player)

    flush = checkFlush(player)
    straight = checkStraight(player)

    if flush and straight:
        if sortedHand[0].rank == 'A':
            return (10, "Royal Flush", sortedHand)
        return (9, "Straight Flush", sortedHand)
    

    if checkFour(counts):
        return(8, "Four of a Kind", sortedHand)

    if checkFullHouse(counts):
        return(7, "Full House", sortedHand)

    if checkFlush(player):
        return(6, "Flush", sortedHand)

    if checkStraight(player):
        return(5, "Straight", sortedHand)

    if checkThree(counts):
        return(4, "Three of a Kind", sortedHand)
    
    if checkTwoPair(counts):
        return (3, "Two Pair", sortedHand)
    
    if checkPair(counts):
        return (2, "One Pair", sortedHand)

    return(1, "High Card", sortedHand)

def suitRank(card):
    suitOrder = {'D': 1, 'C': 2, 'H': 3, 'S': 4}
    return suitOrder[card.suit.upper()]

def sort_by_rank_and_suit(hand):
    return sorted(hand, key=lambda card: (rankValues(card), suitRank(card)), reverse=True)

def compare_highest_card(sortedHand1, sortedHand2):
    if rankValues(sortedHand1[0]) > rankValues(sortedHand2[0]):
        return 1
    elif rankValues(sortedHand1[0]) < rankValues(sortedHand2[0]):
        return 2
    else:
        if suitRank(sortedHand1[0]) > suitRank(sortedHand2[0]):
            return 1
        elif suitRank(sortedHand1[0]) < suitRank(sortedHand2[0]):
            return 2
        else:
            return 0  # Exactly the same card

def tieBreaker(hand1, hand2, handType):
    sortedHand1 = sort_by_rank_and_suit(hand1)
    sortedHand2 = sort_by_rank_and_suit(hand2)

    if handType in ["Flush", "Straight Flush", "Royal Flush", "Straight"]:
        return compare_highest_card(sortedHand1, sortedHand2)

    if handType == "Two Pair":
        pairs1= sorted([card for card in sortedHand1 if sortedHand1.count(card) == 2], key=lambda card: (rankValues(card), suitRank(card)), reverse=True)
        pairs2= sorted([card for card in sortedHand2 if sortedHand2.count(card) == 2], key=lambda card: (rankValues(card), suitRank(card)), reverse=True)
        if len(pairs1) < 2 or len(pairs2) < 2:
            return 0  # Handle case where there are not enough pairs
        kicker1 = [card for card in sortedHand1 if sortedHand1.count(card) == 1][0]
        kicker2 = [card for card in sortedHand2 if sortedHand2.count(card) == 1][0]

        if rankValues(pairs1[0]) > rankValues(pairs2[0]):
            return 1
        elif rankValues(pairs1[0]) < rankValues(pairs2[0]):
            return 2
        elif rankValues(pairs1[1]) > rankValues(pairs2[1]):
            return 1
        elif rankValues(pairs1[1]) < rankValues(pairs2[1]):
            return 2
        else:
            if rankValues(kicker1) > rankValues(kicker2):
                return 1
            elif rankValues(kicker1) < rankValues(kicker2):
                return 2
            else:
                if suitRank(kicker1) > suitRank(kicker2):
                    return 1
                elif suitRank(kicker1) < suitRank(kicker2):
                    return 2
                else:
                    return 0  # Exactly the same hand

    if handType == "One Pair":
        pairs1 = [card for card in sortedHand1 if sortedHand1.count(card) == 2]
        pairs2 = [card for card in sortedHand2 if sortedHand2.count(card) == 2]
        if not pairs1 or not pairs2:
            return 0  # Handle case where there is no pair
        pair1 = pairs1[0]
        pair2 = pairs2[0]
        kicker1 = [card for card in sortedHand1 if sortedHand1.count(card) == 1]
        kicker2 = [card for card in sortedHand2 if sortedHand2.count(card) == 1]
        kicker1.sort(key=lambda card: (rankValues(card), suitRank(card)), reverse=True)
        kicker2.sort(key=lambda card: (rankValues(card), suitRank(card)), reverse=True)

        if rankValues(pair1) > rankValues(pair2):
            return 1
        elif rankValues(pair1) < rankValues(pair2):
            return 2
        else:
            for k1, k2 in zip(kicker1, kicker2):
                if rankValues(k1) > rankValues(k2):
                    return 1
                elif rankValues(k1) < rankValues(k2):
                    return 2
                elif suitRank(k1) > suitRank(k2):
                    return 1
                elif suitRank(k1) < suitRank(k2):
                    return 2
            return 0  # Exactly the same hand

    if handType == "High Card":
        return compare_highest_card(sortedHand1, sortedHand2)

    return 0  # No tie-breaker needed
def printPlayerRanks(playerRanks):
    print("\nPlayer Hands by Rank\n---------------")
    for playerId, handRank, handType, sortedHand in playerRanks:
        for card in sortedHand:
            print(f"{card.rank}{card.suit.upper()}", end=' ')
        print("\n---------------")


main()                
