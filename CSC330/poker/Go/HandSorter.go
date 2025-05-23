package main

import "sort"

func SortHands(hands []*Hand) {
    SortHandsByType(hands)
    SortTies(hands)
}

func SortHandsByType(hands []*Hand) {
    sort.Slice(hands, func(i, j int) bool {
        return hands[i].GetType() > hands[j].GetType()
    })
}

// SortTies splits hands into subarrays of similar types and sorts them
func SortTies(hands []*Hand) {
    var sortedHands []*Hand
    startIndex := 0
    lastType := hands[0].GetType()

    for i, hand := range hands {
        if hand.GetType() != lastType || i == len(hands)-1 {
            if hand.GetType() != lastType {
                sortedHands = append(sortedHands, SortSubarray(hands[startIndex:i])...)
                startIndex = i
            } else {
                sortedHands = append(sortedHands, SortSubarray(hands[startIndex:])...)
            }
            lastType = hand.GetType()
        }
    }
    copy(hands, sortedHands)
}

func SortSubarray(hands []*Hand) []*Hand {
    handType := hands[0].GetType()

    switch handType {
    case 9: // Royal Flush
        sort.Slice(hands, func(i, j int) bool {
            return compareRoyalFlush(hands[i], hands[j]) < 0
        })
    case 8: // Straight Flush
        sort.Slice(hands, func(i, j int) bool {
            return compareStraightFlush(hands[i], hands[j]) < 0
        })
    case 7: // Four of a Kind
        sort.Slice(hands, func(i, j int) bool {
            return compareFourOfAKind(hands[i], hands[j]) < 0
        })
    case 6: // Full House
        sort.Slice(hands, func(i, j int) bool {
            return compareFullHouse(hands[i], hands[j]) < 0
        })
    case 5: // Flush
        sort.Slice(hands, func(i, j int) bool {
            return compareFlush(hands[i], hands[j]) < 0
        })
    case 4: // Straight
        sort.Slice(hands, func(i, j int) bool {
            return compareStraight(hands[i], hands[j]) < 0
        })
    case 3: // Three of a Kind
        sort.Slice(hands, func(i, j int) bool {
            return compareThreeOfAKind(hands[i], hands[j]) < 0
        })
    case 2: // Two Pair
        sort.Slice(hands, func(i, j int) bool {
            return compareTwoPair(hands[i], hands[j]) < 0
        })
    case 1: // Pair
        sort.Slice(hands, func(i, j int) bool {
            return comparePair(hands[i], hands[j]) < 0
        })
    default: // High Card
        sort.Slice(hands, func(i, j int) bool {
            return compareHighCard(hands[i], hands[j]) < 0
        })
    }

    return hands
}

// Compare Functions
func compareRoyalFlush(h1, h2 *Hand) int {
    return compareHighestCard(h1.GetSortedCards(), h2.GetSortedCards())
}

func compareStraightFlush(h1, h2 *Hand) int {
    return compareHighestCard(h1.GetSortedCards(), h2.GetSortedCards())
}

func compareFourOfAKind(h1, h2 *Hand) int {
    c1 := getCardsOccurringNTimes(h1.GetSortedCards(), 4)[0]
    c2 := getCardsOccurringNTimes(h2.GetSortedCards(), 4)[0]
    return compareHighestCard(c1, c2)
}

func compareFullHouse(h1, h2 *Hand) int {
    triplet1 := getCardsOccurringNTimes(h1.GetSortedCards(), 3)[0]
    triplet2 := getCardsOccurringNTimes(h2.GetSortedCards(), 3)[0]
    pair1 := getCardsOccurringNTimes(h1.GetSortedCards(), 2)[0]
    pair2 := getCardsOccurringNTimes(h2.GetSortedCards(), 2)[0]

    // Compare triplets first
    result := compareHighestCard(triplet1, triplet2)
    if result != 0 {
        return result
    }
    // If triplets are equal, compare pairs
    return compareHighestCard(pair1, pair2)
}

func compareFlush(h1, h2 *Hand) int {
    return compareHighestCard(h1.GetSortedCards(), h2.GetSortedCards())
}

func compareStraight(h1, h2 *Hand) int {
    return compareHighestCard(h1.GetSortedCards(), h2.GetSortedCards())
}

func compareThreeOfAKind(h1, h2 *Hand) int {
    return compareHighestCard(getCardsOccurringNTimes(h1.GetSortedCards(), 3)[0], getCardsOccurringNTimes(h2.GetSortedCards(), 3)[0])
}

func compareTwoPair(h1, h2 *Hand) int {
    pairs1 := getCardsOccurringNTimes(h1.GetSortedCards(), 2)
    pairs2 := getCardsOccurringNTimes(h2.GetSortedCards(), 2)

    // Compare highest pair
    result := compareHighestCard(pairs1[0], pairs2[0])
    if result != 0 {
        return result
    }

    // If highest pairs are equal, compare second pair
    return compareHighestCard(pairs1[1], pairs2[1])
}

func comparePair(h1, h2 *Hand) int {
    return compareHighestCard(getCardsOccurringNTimes(h1.GetSortedCards(), 2)[0], getCardsOccurringNTimes(h2.GetSortedCards(), 2)[0])
}

func compareHighCard(h1, h2 *Hand) int {
    return compareHighestCard(h1.GetSortedCards(), h2.GetSortedCards())
}

// Helper Functions
func compareHighestCard(hand1, hand2 []Card) int {
    for i := 0; i < len(hand1); i++ {
        if hand1[i].rank > hand2[i].rank {
            return -1
        } else if hand1[i].rank < hand2[i].rank {
            return 1
        }
        if hand1[i].suit > hand2[i].suit {
            return -1
        } else if hand1[i].suit < hand2[i].suit {
            return 1
        }
    }
    return 0
}

func getCardsOccurringNTimes(cardList []Card, n int) [][]Card {
    rankMap := make(map[int][]Card)
    for _, card := range cardList {
        rankMap[card.rank] = append(rankMap[card.rank], card)
    }
    var result [][]Card
    for _, cards := range rankMap {
        if len(cards) == n {
            result = append(result, cards)
        }
    }
    return result
}

func adjustValue(card Card) int {
    switch card.suit {
    case 1: // Spades
        return card.rank + 10
    case 2: // Hearts
        return card.rank + 5
    case 3: // Clubs
        return card.rank + 2
    default: // Diamonds
        return card.rank
    }
}

