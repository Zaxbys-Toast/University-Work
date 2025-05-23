use core::fmt;

pub const RANK_MAP: [&str; 13] = [
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A",
];
pub const SUIT_MAP: [&str; 4] = ["S", "H", "C", "D"];

#[derive(Clone)]
pub struct Card {
    suit: u32,
    rank: u32,
}

impl Card {
    pub fn new(rank: &str, suit: &str) -> Option<Self> {
        // Find the position of the suit and rank
        let suit_index = SUIT_MAP.iter().position(|&s| s == suit);
        let rank_index = RANK_MAP.iter().position(|&r| r == rank);

        // Check if both the suit and rank are valid
        match (suit_index, rank_index) {
            (Some(s), Some(r)) => Some(Self {
                suit: s as u32,
                rank: r as u32,
            }),
            _ => None, // Return None if invalid
        }
    }

    pub fn get_rank(&self) -> u32 {
        self.rank
    }

    pub fn get_suit(&self) -> u32 {
        self.suit
    }
}

impl fmt::Display for Card {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "{}{}",
            RANK_MAP[self.rank as usize], SUIT_MAP[self.suit as usize]
        )
    }
}

impl PartialOrd for Card {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other)) // Delegate to `Ord` implementation
    }
}

impl Ord for Card {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.rank.cmp(&other.rank)
    }
}

impl PartialEq for Card {
    fn eq(&self, other: &Self) -> bool {
        self.rank == other.rank && self.suit == other.suit
    }
}
impl Eq for Card {}
