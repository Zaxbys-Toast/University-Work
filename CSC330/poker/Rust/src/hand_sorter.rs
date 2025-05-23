use crate::card::Card;
use crate::hand::Hand;

pub fn sort_hands(hands: &mut Vec<Hand>) {
    sort_hands_by_type(hands);
    sort_ties(hands); // Sort ties if necessary
}
fn sort_hands_by_type(hands: &mut Vec<Hand>) {
    hands.sort_by(|a, b| b.get_type().cmp(&a.get_type())); // Sort hands by handType in descending order
}

fn sort_ties(hands: &mut Vec<Hand>) {
    let mut last_type = hands[0].get_type(); // Initialize the first hand type

    // We will keep track of the groups of hands
    let mut groups: Vec<Vec<Hand>> = Vec::new();
    let mut current_group: Vec<Hand> = Vec::new();

    // Iterate through the hands and group them by type
    for i in 0..hands.len() {
        let hand = &hands[i]; // Immutable borrow
        if hand.get_type() != last_type {
            // If the hand type has changed, push the current group to the groups
            groups.push(current_group);
            current_group = Vec::new(); // Reset the current group
        }
        current_group.push(hands[i].clone()); // Add the hand to the current group
        last_type = hand.get_type(); // Update the last hand type
    }

    // Don't forget to add the final group
    groups.push(current_group);

    // Now, for each group, sort it
    for group in groups.iter_mut() {
        group.sort_by(|a, b| compare_hands(a, b));
        group.reverse();
    }

    // After sorting all groups, flatten them back into the original hands vector
    hands.clear(); // Clear the original hands vector to fill it back in sorted order
    for group in groups {
        hands.extend(group); // Add all the sorted hands back to hands
    }
}

fn compare_hands(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    let hand_type = h1.get_type();
    match hand_type {
        Some(9) => compare_royal_flush(h1, h2),
        Some(8) => compare_straight_flush(h1, h2),
        Some(7) => compare_four_of_a_kind(h1, h2),
        Some(6) => compare_full_house(h1, h2),
        Some(5) => compare_flush(h1, h2),
        Some(4) => compare_straight(h1, h2),
        Some(3) => compare_three_of_a_kind(h1, h2),
        Some(2) => compare_two_pair(h1, h2),
        Some(1) => compare_pair(h1, h2),
        _ => compare_high_card(h1, h2), // High Card
    }
}
// Comparison functions for specific hands
fn compare_royal_flush(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_flush(h1, h2)
}
fn compare_straight_flush(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_straight(h1, h2)
}
fn compare_four_of_a_kind(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_n_of_a_kind(h1, h2, 4)
}
fn compare_full_house(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    let three1 = {
        let cards = get_cards_occuring_n_times(&h1.get_sorted_cards(), 3);
        cards.first().cloned().unwrap()
    };
    let three2 = {
        let cards = get_cards_occuring_n_times(&h2.get_sorted_cards(), 3);
        cards.first().cloned().unwrap()
    };
    three1.get_rank().cmp(&three2.get_rank()).then(compare_highest_card(&h1.get_sorted_cards(),&h2.get_sorted_cards()))
}

fn compare_flush(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_highest_card(&h1.get_sorted_cards(), &h2.get_sorted_cards())
}

fn is_low_straight(cards: &[Card]) -> bool {
    cards.len() == 5
        && cards[0].get_rank() == 12
        && cards[1].get_rank() == 3
        && cards[2].get_rank() == 2
        && cards[3].get_rank() == 1
        && cards[4].get_rank() == 0
}

fn compare_straight(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    let cards1 = &h1.get_sorted_cards();
    let cards2 = &h2.get_sorted_cards();
    if is_low_straight(&cards1) {
        if is_low_straight(&cards2) {
            return compare_highest_card(&cards1, &cards2);
        }
        let value1 = 3;
        let value2 = cards2.first().unwrap().get_rank();
        return value1.cmp(&value2);
    } else if is_low_straight(&cards2) {
        let value2 = 3;
        let value1 = cards1.first().unwrap().get_rank();
        return value1.cmp(&value2);
    }
    compare_highest_card(&cards1, &cards2)
}
fn compare_three_of_a_kind(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_n_of_a_kind(h1, h2, 3)
}
fn compare_two_pair(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_pair(h1, h2)
}
fn compare_pair(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_n_of_a_kind(h1, h2, 2)
}
fn compare_high_card(h1: &Hand, h2: &Hand) -> std::cmp::Ordering {
    compare_highest_card(&h1.get_sorted_cards(), &h2.get_sorted_cards())
}
// Compare the highest cards of two hands
fn compare_highest_card(h1: &Vec<Card>, h2: &Vec<Card>) -> std::cmp::Ordering {
    for i in 0..h1.len() {
        let v1 = h1[i].get_rank();
        let v2 = h2[i].get_rank();
        if v1 != v2 {
            return v1.cmp(&v2);
        }
    }
    std::cmp::Ordering::Equal
}
// Compare N of a kind hands
fn compare_n_of_a_kind(h1: &Hand, h2: &Hand, n: usize) -> std::cmp::Ordering {
    let c1 = {
        let binding1 = get_cards_occuring_n_times(&h1.get_sorted_cards(), n);
        match binding1.first() {
            Some(card) => card.clone(),               // Clone the card if it exists
            None => return std::cmp::Ordering::Equal, // Return equal if no card found
        }
    };
    let c2 = {
        let binding2 = get_cards_occuring_n_times(&h2.get_sorted_cards(), n);
        match binding2.first() {
            Some(card) => card.clone(),               // Clone the card if it exists
            None => return std::cmp::Ordering::Equal, // Return equal if no card found
        }
    };
    c1.get_rank().cmp(&c2.get_rank())
}
// Get cards occurring n times in the sorted hand
fn get_cards_occuring_n_times(cards: &Vec<Card>, n: usize) -> Vec<Card> {
    let mut count = std::collections::HashMap::new();
    for card in cards {
        *count.entry(card.get_rank()).or_insert(0) += 1;
    }
    cards
        .iter()
        .filter(|&card| *count.get(&card.get_rank()).unwrap() == n)
        .cloned()
        .collect()
}
