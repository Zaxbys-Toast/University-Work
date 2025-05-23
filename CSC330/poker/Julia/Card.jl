# Julia Card Class
struct Card
    rank::Int
    suit::Int
end

RANK_MAP = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]
SUIT_MAP = ["D", "C", "H", "S"]

# Get the index of the rank in the RANK_MAP (1-based index)
function get_rank_index(rank::String)
    index = findfirst(isequal(rank), RANK_MAP)
    index === nothing && throw(ArgumentError("Invalid card rank: $rank"))
    return index
en

# Get the index of the suit in the SUIT_MAP (1-based index)
function get_suit_index(suit::String)
    index = findfirst(isequal(suit), SUIT_MAP)
    index === nothing && throw(ArgumentError("Invalid card suit: $suit"))
    return index
end

# Accessor functions to get the rank and suit from a Card
function get_rank(card::Card)
    return card.rank
end

function get_suit(card::Card)
    return card.suit
end

# Constructor for Card which converts strings to indices
function Card(rank::String, suit::String)
    # Handle multi-character ranks like "10" explicitly
    if length(rank) > 2
        throw(ArgumentError("Invalid card rank: $rank"))
    end
    rank_index = get_rank_index(rank)
    suit_index = get_suit_index(suit)
    return Card(rank_index, suit_index)
end

# Overload comparison operators
Base.:(<)(card1::Card, card2::Card) = card1.rank < card2.rank
Base.:(==)(card1::Card, card2::Card) = card1.rank == card2.rank && card1.suit == card2.suit

# Custom show function to print the card in a user-friendly format
function Base.show(io::IO, card::Card)
    card_string = RANK_MAP[get_rank(card)] * SUIT_MAP[get_suit(card)]
    PRINT_WIDTH = 4  # Set the width for card printing
    print(io, lpad(card_string, PRINT_WIDTH))
end

function get_value(card::Card)
    return card.rank
end

function to_string(card::Card)
    return "$(RANK_MAP[card.rank])$(SUIT_MAP[card.suit])"
end

