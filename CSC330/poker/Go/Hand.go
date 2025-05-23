package main

import (
	"fmt"
	"sort"
)

const HAND_SIZE = 5

var HAND_MAP = []string{
	"High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
	"Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Straight Flush",
}

// Hand struct
type Hand struct {
	cards   []Card
	handType int
}

// NewHand initializes a new Hand with an empty slice of cards and an invalid type (-1)
func NewHand() *Hand {
	return &Hand{
		cards:   make([]Card, 0),
		handType: -1,
	}
}

// String method to represent a Hand as a string
func (h *Hand) String() string {
	var result string
	for _, card := range h.cards {
		result += fmt.Sprintf("%v ", card)
	}
	if h.handType >= 0 && h.handType < len(HAND_MAP) {
		result += fmt.Sprintf("- %s", HAND_MAP[h.handType])
	} else {
		result += ""
	}
	return result
}

// AddCard method to add a card to the hand
func (h *Hand) AddCard(card Card) {
	h.cards = append(h.cards, card)
}

// GetType method to get the type of the hand
func (h *Hand) GetType() int {
	return h.handType
}

// SetType method to set the type of the hand
func (h *Hand) SetType(t int) {
	h.handType = t
}

// GetSortedCards method to return the sorted cards in the hand based on card rank
func (h *Hand) GetSortedCards() []Card {
	sort.Slice(h.cards, func(i, j int) bool {
		return h.cards[i].rank > h.cards[j].rank
	})
	return h.cards
}

func (h *Hand) cardCount() int {
	return len(h.cards)
}
//================= Main Function for Testing ========================
/*
func main() {
	// Example usage
	hand := NewHand()
	hand.AddCard(Card{rank: 2, suit: 1}) // Add some example cards
	hand.AddCard(Card{rank: 5, suit: 2})
	hand.AddCard(Card{rank: 9, suit: 3})
	hand.AddCard(Card{rank: 12, suit: 1})
	// Set hand type (just as an example)
	hand.SetType(3)

	// Print the hand and its sorted cards
	fmt.Println("Hand:", hand)
	fmt.Println("Sorted Hand:", hand.GetSortedCards())
}
*/
