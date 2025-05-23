require_relative 'card'
require_relative 'hand'

class AssignType2Joker

    # Assign jokers to hand types
    def self.assign_type_2_jokers(hand)
        cards = hand.get_sorted_cards

        if can_be_royal_straight_flush(cards)
            hand.set_type(9)
            assign_jokers_to_royal_straight_flush(hand)
        elsif can_be_straight_flush(cards)
            hand.set_type(8)
            assign_jokers_to_straight_flush(hand)
        elsif can_be_four_of_kind(cards)
            hand.set_type(7)
            assign_jokers_to_four_of_kind(hand)
        elsif can_be_flush(cards)
            hand.set_type(5)
            assign_jokers_to_flush(hand)
        elsif can_be_straight(cards)
            hand.set_type(4)
            assign_jokers_to_straight(hand)
        else
            # At minimum can be a three of a kind
            hand.set_type(3)
            assign_jokers_to_three_of_kind(hand)
        end
    end


    def self.can_be_royal_straight_flush(cards)
        cards_without_jokers = get_list_without_jokers(cards)

        # Check if suits are same
        return false unless can_be_flush(cards_without_jokers)

        # Check if cards are royal cards (10, J, Q, K, A)
        values = cards_without_jokers.map{ |card| card.get_value }
        royal_values = ['10', 'J', 'Q', 'K', 'A']

        # Checks the cards after sorting to ensure royal cards in any order
        return false unless values.sort == royal_values.sort

        return true
    end

    def self.can_be_straight_flush(cards)
        cards_without_jokers = get_list_without_jokers(cards)

        # Returns true if flush and straight
        return false unless can_be_flush(cards_without_jokers) && can_be_straight(cards_without_jokers)
        return true
    end

    def self.can_be_four_of_kind(cards)
        cards_without_jokers = get_list_without_jokers(cards)
        values = cards_without_jokers.map{ |card| card.get_value }
        # 2 Jokers can be added to get a 4 of a kind
        values.any? { |value| values.count(value) == 2 }
    end

    def self.can_be_full_house(cards)
        cards_without_jokers = get_list_without_jokers(cards)
        values = cards_without_jokers.map{ |card| card.get_value }
        # With 2 jokers and 3 cards, any pair can become full house
        values.any? { |value| values.count(value) == 2 }
    end

    def self.can_be_flush(cards)
        cards_without_jokers = get_list_without_jokers(cards)
        suits = cards_without_jokers.map{ |card| card.get_suit }
        suits.all?{ |suit| suit == suits[0] }
    end

    def self.can_be_straight(cards)
        cards_without_jokers = get_list_without_jokers(cards)
        values = cards_without_jokers.map{ |card| card.get_value }
        card_values = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        sorted_values = values.sort_by{ |value| card_values.index(value) }

	# Check for low-Ace
	low_ace = ['A','2','3','4','5']
	if sorted_values.sort == low_ace
	    return true
	end

	# Check for regular straight
        first_pos = card_values.index(sorted_values[0])         # Get the first card value
        last_pos = card_values.index(sorted_values[-1])         # Get the last card value

        last_pos - first_pos <= 4
    end

    def self.can_be_three_of_kind(cards)
        # Three of a kind always works with 2 Jokers
        true
    end

    # ------------------- Methods to assign jokers to hand types ------------------------

    def self.assign_jokers_to_royal_straight_flush(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)
        suit = cards_without_jokers[0].get_suit
        values = cards_without_jokers.map{ |card| card.get_value }

        # Finds which royal cards are missing
        royal_values = ['10', 'J', 'Q', 'K', 'A']
        needed_values = royal_values - values

        # Assign Jokers to missing royal cards
        jokers = hand.cards.select{ |card| is_joker?(card) }    # Gets the 2 Jokers
        jokers[0].set_value(needed_values[0])                   # Sets the first Joker to the needed value
        jokers[0].set_suit(suit)                                # Sets the first Joker to the required suit
        jokers[1].set_value(needed_values[1])                   # Sets the second Joker to the next needed val
        jokers[1].set_suit(suit)                                # Sets the second Joker to the required suit
    end

    def self.assign_jokers_to_straight_flush(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)
        suit = cards_without_jokers[0].get_suit
        values = cards_without_jokers.map{ |card| card.get_value }

        card_values = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        sorted_values = values.sort_by{ |value| card_values.index(value) }

        first_pos = card_values.index(sorted_values[0])
        last_pos = card_values.index(sorted_values[-1])

        # Find missing values in sequence
        needed_values = []
        (first_pos..last_pos).each do |pos|
            value = card_values[pos]
            needed_values << value unless sorted_values.include?(value)
        end

        # Assign jokers
        jokers = hand.cards.select{ |card| is_joker?(card) }
        jokers[0].set_value(needed_values[0])
        jokers[0].set_suit(suit)
        jokers[1].set_value(needed_values[1])
        jokers[1].set_suit(suit)
    end

    def self.assign_jokers_to_four_of_kind(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)
        values = cards_without_jokers.map{ |card| card.get_value }

        # Finds a value that appears twice
        required_value = values.find{ |value| values.count(value) == 2 }

        # Get the suits of the repeating cards
        repeating_cards_suits = cards_without_jokers.map{  |card| card.get_suit }
        available_suits = ['H', 'D', 'C', 'S'] - repeating_cards_suits

        # Make both jokers the required value
        jokers = hand.cards.select{ |card| is_joker?(card) }
        jokers.each do |joker|
            joker.set_value(required_value)
            joker[0].set_suit(available_suits[0])
            joker[1].set_suit(available_suits[1])
        end
    end

    def self.assign_jokers_to_flush(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)
        suit = cards_without_jokers[0].get_suit

        # Get missing card values
        values = cards_without_jokers.map{ |card| card.get_value }
        available_values = ['2','3','4','5','6','7','8','9','10','J','Q','K','A'] - values
        two_highest_values = available_values.sort_by{ |value| values.index(value) }.reverse[0..1]

        # Assign both Jokers to match the suit
        jokers = hand.cards.select{ |card| is_joker?(card) }
        jokers.each do |joker|
            joker.set_suit(suit)
            joker[0].set_value(two_highest_values[0])                           # Assign the Jokers to the highest card value
            joker[1].set_value(two_highest_values[1])
        end
    end

    def self.assign_jokers_to_straight(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)
        values = cards_without_jokers.map{ |card| card.get_value }

        card_values = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        sorted_values = values.sort_by{ |value| card_values.index(value) }

        first_pos = card_values.index(sorted_values[0])
        last_pos = card_values.index(sorted_values[-1])

	# Handles low Ace case
	if sorted_values.include?('A') && sorted_values.include?('2')
	    low_ace = ['A','2','3','4','5']
	    # Existing hand without A
	    no_ace_sorted_values = sorted_values.reject{ |value| value == 'A' }
	    # Moves Ace to the front of sorted hand
	    sorted_values = ['A'] + no_ace_sorted_values
	    sorted_values = sorted_values.sort_by { |value| low_ace.index(value) }
	end

        # Find missing values
        needed_values = []
        (first_pos..last_pos).each do |pos|                                     # Loops through first to last position of the sorted cards
            value = card_values[pos]
            needed_values << value unless sorted_values.include?(value)         # Checks values that are needed and adds to needed_values
        end

        # Assign jokers
        jokers = hand.cards.select{ |card| is_joker?(card) }
	jokers.each_with_index do |joker,index|
            joker.set_value(needed_values[index])
	end
    end

    def self.assign_jokers_to_three_of_kind(hand)
        cards_without_jokers = get_list_without_jokers(hand.cards)

        # Sort the cards in descending order
        card_values = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        sorted_values = cards_without_jokers.sort_by{ |value| card_values.index(value) }.reverse

        required_value = sorted_values[0].get_value

        # Assign both Jokers to first card value
        jokers = hand.cards.select{ |card| is_joker?(card) }
        jokers.each { |joker| joker.set_value(required_value) }
    end

    # -------------------- Helper methods --------------------------
    def self.get_list_without_jokers(cards)
        copied_list = Marshal.load(Marshal.dump(cards))
        copied_list.reject! { |card| is_joker?(card) }
        copied_list.sort_by { |card| card.get_value }
    end

    #Check to see if the card is a joker (only the face not the color)
    def self.is_joker?(card)
        card.get_value == 'X'
    end

end
