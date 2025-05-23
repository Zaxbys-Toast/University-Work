use crate::card::Card;
use crate::hand::Hand;
use std::collections::HashMap;

pub struct HandIdentifier;
impl HandIdentifier {
    pub fn assign_type(hand: &mut Hand) {
        let cards = hand.get_sorted_cards();

        if Self::is_royal_straight_flush(&cards) {
            hand.set_type(9);
        } else if Self::is_straight_flush(&cards) {
            hand.set_type(8);
        } else if Self::is_four_of_a_kind(&cards) {
            hand.set_type(7);
        } else if Self::is_full_house(&cards) {
            hand.set_type(6);
        } else if Self::is_flush(&cards) {
            hand.set_type(5);
        } else if Self::is_straight(&cards) {
            hand.set_type(4);
        } else if Self::is_three_of_a_kind(&cards) {
            hand.set_type(3);
        } else if Self::is_two_pair(&cards) {
            hand.set_type(2);
        } else if Self::is_pair(&cards) {
            hand.set_type(1);
        } else {
            hand.set_type(0); // High Card
        }
    }

    fn is_royal_straight_flush(cards: &[Card]) -> bool {
        Self::is_royal_straight(cards) && Self::is_flush(cards)
    }

    fn is_royal_straight(cards: &[Card]) -> bool {
        cards.len() == 5
            && cards[0].get_rank() == 12
            && cards[1].get_rank() == 11
            && cards[2].get_rank() == 10
            && cards[3].get_rank() == 9
            && cards[4].get_rank() == 8
    }

    fn is_low_straight(cards: &[Card]) -> bool {
        cards.len() == 5
            && cards[0].get_rank() == 12
            && cards[1].get_rank() == 3
            && cards[2].get_rank() == 2
            && cards[3].get_rank() == 1
            && cards[4].get_rank() == 0
    }

    fn is_straight_flush(cards: &[Card]) -> bool {
        Self::is_straight(cards) && Self::is_flush(cards)
    }

    fn is_flush(cards: &[Card]) -> bool {
        cards
            .iter()
            .all(|card| card.get_suit() == cards[0].get_suit())
    }

    fn is_straight(cards: &[Card]) -> bool {
        Self::is_royal_straight(cards)
            || Self::is_low_straight(cards)
            || cards
                .windows(2)
                .all(|pair| pair[0].get_rank() == pair[1].get_rank() + 1)
    }

    fn get_frequency_rank(cards: &[Card]) -> Vec<usize> {
        let mut rank_counts = HashMap::new();

        for card in cards {
            *rank_counts.entry(card.get_rank() as u8).or_insert(0) += 1;
        }

        // Convert to a sorted vector of frequencies
        let mut counts = rank_counts.values().copied().collect::<Vec<_>>();
        counts.sort_unstable();
        counts
    }

    fn is_four_of_a_kind(cards: &[Card]) -> bool {
        let counts = Self::get_frequency_rank(cards);
        counts == vec![1, 4]
    }

    fn is_full_house(cards: &[Card]) -> bool {
        let counts = Self::get_frequency_rank(cards);
        counts == vec![2, 3]
    }

    fn is_three_of_a_kind(cards: &[Card]) -> bool {
        let counts = Self::get_frequency_rank(cards);
        counts == vec![1, 1, 3]
    }

    fn is_two_pair(cards: &[Card]) -> bool {
        let counts = Self::get_frequency_rank(cards);
        counts == vec![1, 2, 2]
    }

    fn is_pair(cards: &[Card]) -> bool {
        let counts = Self::get_frequency_rank(cards);
        counts == vec![1, 1, 1, 2]
    }
}
