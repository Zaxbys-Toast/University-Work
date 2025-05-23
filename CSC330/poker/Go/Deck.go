package main

import (
	"fmt"
	"math/rand"
	"time"
)

type Deck struct {
	cards []Card
}

// NewDeck creates a standard 52-card deck
func NewDeck() Deck {
	var cards []Card
	for suit := 0; suit < len(SUIT_MAP); suit++ {
		for rank := 0; rank < len(RANK_MAP); rank++ {
			cards = append(cards, Card{rank: rank, suit: suit})
		}
	}
	return Deck{cards: cards}
}

// Shuffle randomizes the order of cards in the deck
func (d *Deck) Shuffle() {
	rand.Seed(time.Now().UnixNano())
	rand.Shuffle(len(d.cards), func(i, j int) {
		d.cards[i], d.cards[j] = d.cards[j], d.cards[i]
	})
}

// DealCard removes and returns the top card of the deck
func (d *Deck) DealCard() (Card, error) {
	if len(d.cards) == 0 {
		return Card{}, fmt.Errorf("no cards left in the deck")
	}
	card := d.cards[0]
	d.cards = d.cards[1:]
	return card, nil
}

// String returns a string representation of the deck
func (d Deck) String() string {
	var deckStr string
	for i, card := range d.cards {
		if i % 13 == 0 && i != 0{
			deckStr += "\n"
		}
		deckStr += card.String() + "  "
	}
	return deckStr
}
//=================== Main Function for Testing ====================
/*
func main() {
	// Create a new deck
	deck := NewDeck()
	fmt.Println("Original Deck:")
	fmt.Println(deck)

	// Shuffle the deck
	deck.Shuffle()
	fmt.Println("\nShuffled Deck:")
	fmt.Println(deck)

	// Deal a card
	card, err := deck.DealCard()
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("\nDealt Card:", card)
	}

	// Print the remaining deck
	fmt.Println("\nRemaining Deck:")
	fmt.Println(deck)
}
*/
