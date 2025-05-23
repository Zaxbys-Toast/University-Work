use crate::card::Card;
use std::fmt;
// Constants for hand size and hand ranking names
const HAND_SIZE: usize = 5;
const HAND_MAP: [&str; 10] = [
    "High Card",
    "Pair",
    "Two Pair",
    "Three of a Kind",
    "Straight",
    "Flush",
    "Full House",
    "Four of a Kind",
    "Straight Flush",
    "Royal Straight Flush",
];
// The Hand struct
#[derive(Clone)]
pub struct Hand {
    cards: Vec<Card>,
    hand_type: Option<usize>, // None indicates an invalid hand type
}
impl Hand {
    // Constructor for a new hand
    pub fn new() -> Self {
        Self {
            cards: Vec::with_capacity(HAND_SIZE), // Allocate space for 5 cards
            hand_type: None,                      // Initially, no hand type
        }
    }
    // Add a card to the hand
    pub fn add_card(&mut self, card: Card) {
        self.cards.push(card);
    }
    // Get the hand type
    pub fn get_type(&self) -> Option<usize> {
        self.hand_type
    }
    // Set the hand type
    pub fn set_type(&mut self, hand_type: usize) {
        self.hand_type = Some(hand_type);
    }
    // Get the sorted cards
    pub fn get_sorted_cards(&self) -> Vec<Card> {
        let mut sorted_cards = self.cards.clone();
        sorted_cards.sort_by(|a, b| b.get_rank().cmp(&a.get_rank()));
        sorted_cards
    }

    pub fn card_count(&self) -> usize {
        self.cards.len() // Returns the number of cards in the hand
    }
}
// Implement the Display trait for Hand
impl fmt::Display for Hand {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut result = String::new();
        for card in &self.cards {
            result.push_str(&format!("{} ", card)); // Format each card
        }
        if let Some(hand_type) = self.hand_type {
            if hand_type < HAND_MAP.len() {
                result.push_str(&format!("- {}", HAND_MAP[hand_type]));
            } else {
                result.push_str("");
            }
        } else {
            result.push_str("");
        }
        write!(f, "{}", result)
    }
}
impl IntoIterator for Hand {
    type Item = Card;
    type IntoIter = std::vec::IntoIter<Card>;

    fn into_iter(self) -> Self::IntoIter {
        self.cards.into_iter()
    }
}
impl<'a> IntoIterator for &'a Hand {
    type Item = &'a Card;
    type IntoIter = std::slice::Iter<'a, Card>;

    fn into_iter(self) -> Self::IntoIter {
        self.cards.iter()
    }
}
