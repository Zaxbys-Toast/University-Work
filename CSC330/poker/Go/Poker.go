package main
import (
	"fmt"
	"os"
	"bufio"
	"strings"
)

func checkForDuplicates(card Card, dealtCards map[int]bool) {
	cardKey := card.getRank() * 4 + card.getSuit() // Combine rank and suit to form a unique key
	if dealtCards[cardKey] {
		panic(fmt.Sprintf("Error: Duplicate card detected: %s%s", card.rank, card.suit))
	}
	dealtCards[cardKey] = true
}
func main() {
// ======================= Set up ===========================
        fmt.Println("*** P O K E R  H A N D  A N A L Y Z E R ***\n\n")
	// Create 6 hands
	hands := make([]*Hand, 6)
	for i := range hands {
		hands[i] = NewHand()
	}
	if(len(os.Args) > 1){
// ================= Using Test Deck =======================
		dealtCards := make(map[int]bool)
		currentHand := 0
		filename := os.Args[1]
		fmt.Printf("*** File: %s\n\n", filename)
		// Open the file
		file, err := os.Open(filename)
		if err != nil {
			fmt.Printf("Error opening file: %v\n", err)
			return
		}
		defer file.Close()

		// Read all from file
		var allLines []string
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			allLines = append(allLines, scanner.Text())
		}
		if err := scanner.Err(); err != nil {
			fmt.Printf("Error reading file: %v\n", err)
		return
		}

		// Split into tokens
		for _, line := range allLines {
			tokens := strings.Split(line, ",")
			for i := range tokens {
				tokens[i] = strings.TrimSpace(tokens[i])
			}

		// Process each token
			for _, token := range tokens {
				if len(token) < 2 {
					continue // Skip invalid tokens
				}

				// Extract rank and suit as strings
				rank := token[:len(token)-1] // All except the last character
				suit := token[len(token)-1:] // Last character

				// Create a new Card using the constructor
				card, err := NewCard(rank, suit)
				if err != nil {
					fmt.Println("Unknown Card")
				}
				// Check for duplicates
				checkForDuplicates(card, dealtCards)

				// Add the card to the current hand
				hands[currentHand].AddCard(card)

				// Move to the next hand after 5 cards
				if hands[currentHand].cardCount() == 5 {
					currentHand++
				}
			}

		}

		fmt.Println("\n*** Here are the six hands: ")
                for _, hand := range hands {
                        fmt.Println(hand)
                }
                for _, hand := range hands {
                        hand.AssignType()
                }

	} else {

// ===================== Random Hands =======================

		fmt.Println("*** Using Random Deck ***\n")
		// Create a new deck
		deck := NewDeck()

		// Shuffle the deck
		deck.Shuffle()


		// Print the initial Deck
		fmt.Println(deck)

		// Deal 5 cards to each hand
		for i := 0; i < 5; i++ {
			for j := 0; j < 6; j++ {
				card, err := deck.DealCard()
				if err != nil {
					fmt.Println("Error dealing card:", err)
					return
				}
				hands[j].AddCard(card)
			}
		}

		// Display each hand and its sorted cards
		fmt.Println("\n*** Here are the six hands: ")
		for _, hand := range hands {
			fmt.Println(hand)
		}
		for _, hand := range hands {
			hand.AssignType()
		}
		fmt.Println("\n*** Here is what remains in the deck:")
		fmt.Println(deck)
	}
	fmt.Println("\n--- WINNING HAND ORDER ---")
	SortHands(hands)
	for _, hand := range hands {
		fmt.Println(hand)
	}

}
