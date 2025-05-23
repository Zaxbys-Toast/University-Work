public class Card {
    private final String rank;
    private final String suit;

    public Card(String cardStr) {
        this.rank = cardStr.substring(0, 1); // First character
        this.suit = cardStr.substring(1); // Second character
    }

    public String getRank() {
        return rank;
    }

    public String getSuit() {
        return suit;
    }

    public int getRankValue() {
        return "23456789TJQKA".indexOf(rank);
    }

    public int getSuitValue() {
        return "SHCD".indexOf(suit);
    }

    public String toString() {
        return rank + suit;
    }
}

