include("Card.jl")

# number of cards per hand and the different hand types
const HAND_SIZE = 5
const HAND_MAP = ["High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
                  "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Straight Flush"]

# Hand struct
mutable struct Hand
    cards::Vector{Card}
    type::Int          
    
    function Hand()
        new([], -1)  # Initialize with an empty cards array and an invalid type (-1)
    end
end

# String representation of the Hand object
function Base.show(io::IO, hand::Hand)
    result = ""
    for card in hand.cards
        result *= string(card)
    end
    print(io, result)
end

# Add a card to the hand
function add_card!(hand::Hand, card)
    push!(hand.cards, card)
end

# Get the type of the hand
function get_type(hand::Hand)
    return hand.type
end

# Set the type of the hand
function set_type(hand::Hand, t::Int)
    hand.type = t
end

# Get sorted cards
function get_sorted_cards(hand::Hand)
	sort(hand.cards, by = card -> get_value(card))
end

