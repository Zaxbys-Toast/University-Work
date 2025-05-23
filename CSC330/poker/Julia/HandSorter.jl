include("HandIdentifier.jl")
include("Card.jl")


function sort_hands!(hands)
    sort_hands_by_type!(hands)
    sort_ties!(hands)
end

function sort_hands_by_type!(hands)
    sort!(hands, by=h -> get_type(h), rev=true)  # Fixed: get_type should be called as a function
end

function sort_ties!(hands)
    start_index = 1
    last_type = get_type(hands[1])  # Fixed: get_type should be called as a function

    for i in 1:length(hands)
        hand = hands[i]
        if get_type(hand) != last_type  # Fixed: get_type should be called as a function
            hands[start_index:i-1] = sort_subarray(hands[start_index:i-1])
            start_index = i
            last_type = get_type(hand)  # Fixed: get_type should be called as a function
        elseif i == length(hands)
            hands[start_index:i] = sort_subarray(hands[start_index:i])
        end
    end
end

function sort_subarray(hands)
    hand_type = get_type(hands[1])  # Fixed: get_type should be called as a function

    if hand_type == 9
        return sort!(hands, by=h -> compare_royal_flush(h, hands[1]), rev=true)
    elseif hand_type == 8
        return sort!(hands, by=h -> compare_straight_flush(h, hands[1]), rev=true)
    elseif hand_type == 7
        return sort!(hands, by=h -> compare_four_of_a_kind(h, hands[1]), rev=true)
    elseif hand_type == 6
        return sort!(hands, by=h -> compare_full_house(h, hands[1]), rev=true)
    elseif hand_type == 5
        return sort!(hands, by=h -> compare_flush(h, hands[1]), rev=true)
    elseif hand_type == 4
        return sort!(hands, by=h -> compare_straight(h, hands[1]), rev=true)
    elseif hand_type == 3
        return sort!(hands, by=h -> compare_three_of_a_kind(h, hands[1]), rev=true)
    elseif hand_type == 2
        return sort!(hands, by=h -> compare_two_pair(h, hands[1]), rev=true)
    elseif hand_type == 1
        return sort!(hands, by=h -> compare_pair(h, hands[1]), rev=true)
    else
        return sort!(hands, by=h -> compare_high_card(h, hands[1]), rev=true)
    end
end

function compare_royal_flush(h1, h2)
    return get_suit(get_sorted_cards(h1)[1]) < get_suit(get_sorted_cards(h2)[1]) ? -1 : 1  # Fixed: get_suit and get_sorted_cards should be called as functions
end

function compare_straight(h1, h2)
    l1, l2 = get_sorted_cards(h1), get_sorted_cards(h2)
    highest_card_comparison = compare_highest_card(l1, l2)
    if highest_card_comparison != 0
        return highest_card_comparison
    end

    suit1 = is_royal_straight(l1) ? get_suit(l1[1]) : get_suit(l1[end])  # Fixed: get_suit should be called as a function
    suit2 = is_royal_straight(l2) ? get_suit(l2[1]) : get_suit(l2[end])  # Fixed: get_suit should be called as a function
    return suit1 < suit2 ? -1 : 1
end

function compare_straight_flush(h1, h2)
    l1, l2 = get_sorted_cards(h1), get_sorted_cards(h2)
    highest_card_comparison = compare_highest_card(l1, l2)
    if highest_card_comparison != 0
        return highest_card_comparison
    end
    return get_suit(l1[1]) < get_suit(l2[1]) ? -1 : 1  # Fixed: get_suit should be called as a function
end

function compare_four_of_a_kind(h1, h2)
    c1 = get_cards_occuring_n_times(get_sorted_cards(h1), 4)[1]
    c2 = get_cards_occuring_n_times(get_sorted_cards(h2), 4)[1]
    return compare_card_values(c1, c2)
end

function compare_full_house(h1, h2)
    c1 = get_cards_occuring_n_times(get_sorted_cards(h1), 3)[1]
    c2 = get_cards_occuring_n_times(get_sorted_cards(h2), 3)[1]
    return compare_card_values(c1, c2)
end

function compare_flush(h1, h2)
    l1, l2 = get_sorted_cards(h1), get_sorted_cards(h2)
    highest_card_comparison = compare_highest_card(l1, l2)
    return highest_card_comparison != 0 ? highest_card_comparison : (get_suit(l1[1]) < get_suit(l2[1]) ? -1 : 1)  # Fixed: get_suit should be called as a function
end

function compare_three_of_a_kind(h1, h2)
    c1 = get_cards_occuring_n_times(get_sorted_cards(h1), 3)[1]
    c2 = get_cards_occuring_n_times(get_sorted_cards(h2), 3)[1]
    return compare_card_values(c1, c2)
end

function compare_two_pair(h1, h2)
    pairs1 = get_cards_occuring_n_times(get_sorted_cards(h1), 2)
    pairs2 = get_cards_occuring_n_times(get_sorted_cards(h2), 2)
    highest_card_comparison = compare_highest_card(pairs1, pairs2)
    return highest_card_comparison != 0 ? highest_card_comparison : compare_highest_card(get_cards_occuring_n_times(get_sorted_cards(h1), 1), get_cards_occuring_n_times(get_sorted_cards(h2), 1))
end

function compare_pair(h1, h2)
    pairs1 = get_cards_occuring_n_times(get_sorted_cards(h1), 2)
    pairs2 = get_cards_occuring_n_times(get_sorted_cards(h2), 2)
    return compare_highest_card(pairs1, pairs2)
end

function compare_high_card(h1, h2)
    l1, l2 = get_sorted_cards(h1), get_sorted_cards(h2)
    return compare_highest_card(l1, l2)
end

function compare_highest_card(l1, l2)
    value_list1 = map(c -> get_value(c), l1)
    value_list2 = map(c -> get_value(c), l2)
    sort!(value_list1, rev=true)
    sort!(value_list2, rev=true)

    for (v1, v2) in zip(value_list1, value_list2)
        if v1 == 0 || v2 == 0
	    if v1 == 1
		return 1
	    elseif v2 == 1
		return -1
	    end
	end    
	if v1 < v2
            return -1
        elseif v1 > v2
            return 1
        end
    end
    return 0
end

function get_cards_occuring_n_times(card_list, n)
    return [card for card in unique(card_list) if count(x -> x == card, card_list) == n]
end

