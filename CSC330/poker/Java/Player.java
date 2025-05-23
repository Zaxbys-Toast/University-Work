import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class Player {
    private final List<Card> hand;

    public Player() {
        hand = new ArrayList<>();
    }

    public void dealCard(Card card) {
        hand.add(card);
    }

    public List<Card> getHand() {
        return hand;
    }

    public void sortByRank() {
        Collections.sort(hand, (c1, c2) -> {
            int rankComparison = Integer.compare(c2.getRankValue(), c1.getRankValue());
            return rankComparison != 0 ? rankComparison : Integer.compare(c1.getSuitValue(), c2.getSuitValue());
        });
    }

    public int handRank() {
        sortByRank();
        if (isRoyalFlush()) return 10;
        if (isStraightFlush()) return 9;
        if (isFourOfAKind()) return 8;
        if (isFullHouse()) return 7;
        if (isFlush()) return 6;
        if (isStraight()) return 5;
        if (isThreeOfAKind()) return 4;
        if (isTwoPair()) return 3;
        if (isOnePair()) return 2;
        return 1; // High card
    }

private boolean isRoyalFlush() {
        return isStraightFlush() && hand.get(0).getRank().equals("A");
    }

    private boolean isStraightFlush() {
        return isFlush() && isStraight();
    }

    private boolean isFourOfAKind() {
        return hasSameRank(4);
    }

    private boolean isFullHouse() {
        return hasSameRank(3) && hasSameRank(2);
    }

    private boolean isFlush() {
        String suit = hand.get(0).getSuit();
        for (Card card : hand) {
            if (!card.getSuit().equals(suit)) return false;
        }
        return true;
    }

    private boolean isStraight() {
        for (int i = 0; i < hand.size() - 1; i++) {
            int currentRank = hand.get(i).getRankValue();
            int nextRank = hand.get(i + 1).getRankValue();
            if (currentRank - nextRank != 1) return false;
        }
        return true;
    }

    private boolean isThreeOfAKind() {
        return hasSameRank(3);
    }

    private boolean isTwoPair() {
        int pairCount = 0;
        Map<String, Integer> rankCount = countRanks();
        for (int count : rankCount.values()) {
            if (count == 2) pairCount++;
        }
        return pairCount == 2;
    }

    private boolean isOnePair() {
        return hasSameRank(2);
    }

    private boolean hasSameRank(int n) {
        Map<String, Integer> rankCount = countRanks();
        for (int count : rankCount.values()) {
            if (count == n) return true;
        }
        return false;
    }

    private Map<String, Integer> countRanks() {
        Map<String, Integer> rankCount = new HashMap<>();
        for (Card card : hand) {
            rankCount.put(card.getRank(), rankCount.getOrDefault(card.getRank(), 0) + 1);
        }
        return rankCount;
    }

    public void printHand() {
        hand.forEach(card -> System.out.print(card + " "));
    }
}

