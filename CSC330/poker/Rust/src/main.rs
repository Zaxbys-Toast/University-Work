// Mod statements
mod card;
mod deck;
mod hand;
mod hand_identifier;
mod hand_sorter;

// Use statements
use crate::deck::Deck;
use crate::hand_identifier::HandIdentifier;
use card::*;
use hand::*;
use hand_sorter::*;
use std::env;
use std::path::Path;
use std::fs::File;
use std::io::BufRead;
use std::io;



    // A helper function to check for duplicates
fn check_for_duplicates(dealt_cards: &mut Vec<u8>, card: &Card) {
    let rank_value = card.get_rank();  // Rank is already an integer
    let suit_value = card.get_suit();  // Suit is already an integer
    // Calculate unique card ID (rank * suit combination)
    let card_id = (rank_value * 4) + (suit_value);  
    
    // Check if the card has already been dealt
    if dealt_cards[card_id as usize] == 1 {
       // Duplicate detected, print the card's string representation and panic
       let card_str = card.to_string();
       panic!("Error: Duplicate card detected {}. Program will stop.", card_str);
     } else {
        // Mark the card as dealt
        dealt_cards[card_id as usize] = 1;
     }
}

fn main() -> io::Result<()>{
    // =========== Set up ===========
    println!("*** P O K E R  H A N D  A N A L Y Z E R ***\n\n");
    // Create 6 empty hands
    let mut hands: Vec<Hand> = Vec::new();
    for _ in 0..6 {
        hands.push(Hand::new());
    }
    let mut dealt_cards = vec![0; 53]; // 0 means card has not been dealt
    let args: Vec<_> = env::args().collect();
    // ========= Test Deck ==========
    if args.len() > 1 {
        println!("*** USING TEST DECK ***\n");
        let filename = &args[1];
        println!("*** File: {} ***\n", filename);

        let path = Path::new(filename);
        let file = File::open(path).expect("Couldn't open file");
        let lines = io::BufReader::new(file).lines();

        let mut current_hand = 0;

        for line in lines {
            let line = line?;
            let tokens: Vec<&str> = line.split(',').map(|t| t.trim()).collect();

            for token in tokens {
                let rank = &token[..token.len() - 1];
                let suit = &token[token.len() - 1 .. token.len()];

                let card = Card::new(rank, suit);

                hands[current_hand].add_card(card.expect("REASON"));

                if hands[current_hand].card_count() == 5 {
                    current_hand += 1;
                }
            }
        }
        for hand in &hands {
            for card in hand {
		        check_for_duplicates(&mut dealt_cards, &card); 
            }
        }
        for hand in &hands {
            println!("{}", hand);
        }
    } else {
        // =========== Random ===========
        println!("*** USING RANDOMIZED DECK OF CARDS ***\n");
        let mut d = Deck::new();

        d.shuffle();
        println!("*** Shuffled 52 card deck:");
        d.show();

        // Step 4: Deal 5 cards to each hand
        for _ in 0..5 {
            for hand in &mut hands {
                if let Some(card) = d.deal() {
                    hand.add_card(card);
                } else {
                    println!("Deck is out of cards!");
                    return Ok(());
                }
            }
        }

        println!("\n*** Here are the six hands...");
        for hand in &hands {
            println!("{}", hand);
        }

        println!("\n*** Here is what remains in the deck...");
        d.show();
    }
    // ======== Analysis =======
    println!("\n--- WINNING HAND ORDER ---");

    for hand in &mut hands {
        HandIdentifier::assign_type(hand); // Assigns the appropriate type based on hand cards
    }
    sort_hands(&mut hands);
    for hand in &hands {
        println!("{}", hand);
    }
    Ok(())

}
