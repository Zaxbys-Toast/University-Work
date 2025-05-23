include("Hand.jl")
include("Card.jl")

function assign_type!(hand::Hand)
    cards = get_sorted_cards(hand)

    if is_royal_straight_flush(cards)
        set_type!(hand, 9)
    elseif is_straight_flush(cards)
        set_type!(hand, 8)
    elseif is_four_of_a_kind(cards)
        set_type!(hand, 7)
    elseif is_full_house(cards)
        set_type!(hand, 6)
    elseif is_flush(cards)
        set_type!(hand, 5)
    elseif is_straight(cards)
        set_type!(hand, 4)
    elseif is_three_of_a_kind(cards)
        set_type!(hand, 3)
    elseif is_two_pair(cards)
        set_type!(hand, 2)
    elseif is_pair(cards)
        set_type!(hand, 1)
    else
        set_type!(hand, 0)  # High Card
    end
end

function is_royal_straight_flush(cards::Vector{Card})
    return is_royal_straight(cards) && is_flush(cards)
end

function is_royal_straight(cards::Vector{Card})
    return get_value(cards[1]) == 9 &&
           get_value(cards[2]) == 10 &&
           get_value(cards[3]) == 11 &&
           get_value(cards[4]) == 12 &&
           get_value(cards[5]) == 13
end
function is_low_straight(cards::Vector{Card})
    return get_value(cards[1]) == 1 &&
           get_value(cards[2]) == 2 &&
           get_value(cards[3]) == 3 &&
           get_value(cards[4]) == 4 &&
           get_value(cards[5]) == 13
end

function is_straight_flush(cards::Vector{Card})
    return is_straight(cards) && is_flush(cards)
end

function is_flush(cards::Vector{Card})
    prev_suit = get_suit(cards[1])
    for card in cards
        if get_suit(card) != prev_suit
            return false
        end
    end
    return true
end

function is_straight(cards::Vector{Card})
    return is_low_straight(cards) || begin
        prev_value = get_value(cards[1]) - 1
        for card in cards
            curr_value = get_value(card)
            if curr_value != prev_value + 1
                return false
            end
            prev_value = curr_value
        end
        return true
    end
end

function get_frequency_rank(cards::Vector{Card})
    ranks = [get_value(card) for card in cards] 
    rank_counts = Dict{Int, Int}()
    
    for rank in ranks
        rank_counts[rank] = get(rank_counts, rank, 0) + 1
    end
    
    return rank_counts
end

function is_four_of_a_kind(cards::Vector{Card})
    rank_counts = get_frequency_rank(cards)
    return sort(collect(values(rank_counts))) == [1, 4]
end

function is_full_house(cards::Vector{Card})
    rank_counts = get_frequency_rank(cards)
    return sort(collect(values(rank_counts))) == [2, 3]
end

function is_three_of_a_kind(cards::Vector{Card})
    rank_counts = get_frequency_rank(cards)
    return sort(collect(values(rank_counts))) == [1, 1, 3]
end

function is_two_pair(cards::Vector{Card})
    rank_counts = get_frequency_rank(cards)
    return sort(collect(values(rank_counts))) == [1, 2, 2]
end

function is_pair(cards::Vector{Card})
    rank_counts = get_frequency_rank(cards)
    return sort(collect(values(rank_counts))) == [1, 1, 1, 2]
end

# Mutator function to set the hand type
function set_type!(hand::Hand, t::Int)
    hand.type = t
end

 

