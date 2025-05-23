package main

import (
	"fmt"
	"strings"
)

type Card struct {
	rank int
	suit int
}

var RANK_MAP = []string{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}

var SUIT_MAP = []string{"D", "C", "H", "S"}

func find_index(value string, mapArray []string) int {
	for i, v := range mapArray {
		if v == value {
			return i
		}
	}
	return -1
}

func NewCard(rank string, suit string) (Card, error) {
	rank_index := find_index(strings.ToUpper(rank), RANK_MAP)
	suit_index := find_index(strings.ToUpper(suit), SUIT_MAP)
	if rank_index == -1 || suit_index == -1 {
		return Card{}, fmt.Errorf("invalid rank or suit: %s of %s", rank, suit)
	}
	return Card{rank: rank_index, suit: suit_index}, nil
}

func (c Card) String() string {
	return fmt.Sprintf("%s%s", RANK_MAP[c.rank], SUIT_MAP[c.suit])
}

func (c Card) GetValue() int {
	return c.rank
}

func (c Card) getRank() int {
	return c.rank
}

func (c Card) getSuit() int {
	return c.suit
}
//================== Main function for testing ==================
/*func main() {

        card, err:= NewCard("K", "S")
        fmt.Println(card)
	if err != nil {
		fmt.Println(err)
	}
}*/


