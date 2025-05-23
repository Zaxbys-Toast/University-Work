import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Deck {
    private final List<Card> cards;

    public Deck() {
        cards = new ArrayList<>();
        String ranks = "23456789TJQKA";
        String suits = "SHCD";

        for (char suit : suits.toCharArray()) {
            for (char rank : ranks.toCharArray()) {
                cards.add(new Card("" + rank + suit));
            }
        }
    }

    public void shuffle() {
        Collections.shuffle(cards);
    }

    public Card deal() {
        return cards.remove(cards.size() - 1);
    }

    public void printDeck() {
	for (Card card : cards) {
	    System.out.print(card.toString() + " ");
	}
    }
}

