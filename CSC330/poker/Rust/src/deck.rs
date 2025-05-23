use crate::card;

pub struct Deck {
    cards: Vec<card::Card>,
}

impl Deck {
    pub fn new() -> Self {
        let mut cards = Vec::new();
        for suit in card::SUIT_MAP {
            for rank in card::RANK_MAP {
                if let Some(card) = card::Card::new(rank, suit) {
                    cards.push(card);
                }
            }
        }

        Self { cards }
    }

    pub fn shuffle(&mut self) {
        use rand::seq::SliceRandom;
        let mut rng = rand::thread_rng();
        self.cards.shuffle(&mut rng);
    }

    pub fn deal(&mut self) -> Option<card::Card> {
        self.cards.pop()
    }

    pub fn show(&self) {
        for (i, card) in self.cards.iter().enumerate() {
            print!("{}  ", card); // Print the card with two spaces

            // Add a newline after every 13 cards
            if (i + 1) % 13 == 0 {
                println!();
            }
        }

        // Ensure there's a final newline if the last line isn't complete
        if self.cards.len() % 13 != 0 {
            println!();
        }
    }
}
