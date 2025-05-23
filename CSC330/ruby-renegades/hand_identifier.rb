class HandIdentifier

    def self.assign_type(hand)
        cards = hand.get_sorted_cards

        if is_royal_straight_flush(cards)
            hand.set_type(9)
        elsif is_straight_flush(cards)
            hand.set_type(8)
        elsif is_four_of_a_kind(cards)
            hand.set_type(7)
        elsif is_full_house(cards)
            hand.set_type(6)
        elsif is_flush(cards)
            hand.set_type(5)
        elsif is_straight(cards)
            hand.set_type(4)
        elsif is_three_of_a_kind(cards)
            hand.set_type(3)
        elsif is_two_pair(cards)
            hand.set_type(2)
        elsif is_pair(cards)
            hand.set_type(1)
        else
            hand.set_type(0)  # High Card
        end
    end

    def self.is_royal_straight_flush(cards)
        is_royal_straight(cards) && is_flush(cards)
    end

    def self.is_royal_straight(cards)
        cards[0].get_value == 0 &&
        cards[1].get_value == 9 &&
        cards[2].get_value == 10 &&
        cards[3].get_value == 11 &&
        cards[4].get_value == 12
    end
    
    def self.is_straight_flush(cards)
        is_straight(cards) && is_flush(cards)
    end

    def self.is_flush(cards)
        prev_suit = cards[0].get_suit

        cards.all? do |card|
            if card.get_suit != prev_suit
                return false
            end
            prev_suit = card.get_suit
        end
        true
    end

    def self.is_straight(cards)
        return true if is_royal_straight(cards)
        prev_value = cards[0].get_value - 1
        
        cards.each do |card|
            curr_value = card.get_value
            return false if curr_value != prev_value + 1
            prev_value = curr_value
        end 
        true
    end

    def self.get_frequency_rank(cards)
        rank_counts = Hash.new(0)

        cards.each do |card|
            rank_counts[card.get_value] += 1  # Use get_value for rank
        end

        rank_counts
    end

   
    def self.is_four_of_a_kind(cards)
        rank_counts = get_frequency_rank(cards)

        rank_counts.values.sort == [1, 4]
    end

    def self.is_full_house(cards)
        rank_counts = get_frequency_rank(cards)

        rank_counts.values.sort == [2, 3]
    end

    def self.is_three_of_a_kind(cards)
        rank_counts = get_frequency_rank(cards)

        rank_counts.values.sort == [1, 1, 3]
    end

    def self.is_two_pair(cards)
        rank_counts = get_frequency_rank(cards)

        rank_counts.values.sort == [1, 2, 2]
    end

    def self.is_pair(cards)
        rank_counts = get_frequency_rank(cards)

        rank_counts.values.sort == [1, 1, 1, 2]
    end

end
