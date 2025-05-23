using System;
using System.Collections.Generic;
using System.Linq;

public class Deck
{
    private List<Card> cards;

    public Deck()
    {
        char[] ranks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
        char[] suits = { 'H', 'D', 'S', 'C' };
        cards = new List<Card>();

        foreach (char suit in suits)
        {
            foreach (char rank in ranks)
            {
                cards.Add(new Card(rank, suit));
            }
        }
    }

    public void Shuffle()
    {
        Random rng = new Random();
        int n = cards.Count;

        // Fisher-Yates shuffle algorithm
        while (n > 1)
        {
            int k = rng.Next(n--);
            Card temp = cards[n];
            cards[n] = cards[k];
            cards[k] = temp;
        }
    }

    public Card Deal()
    {
        if (cards.Count == 0)
        {
            throw new InvalidOperationException("No cards left in the deck.");
        }

        Card card = cards[^1]; // Get the last card
        cards.RemoveAt(cards.Count - 1); // Remove the last card

        return card;
    }

    public void PrintDeck() {
	int i = 0;
	foreach ( Card card in cards ) {
	    i++;
	    if(i % 12 == 0) {
		Console.WriteLine();
	    }
	    Console.Write(card.ToString() + " ");
	
	}
    }
}

