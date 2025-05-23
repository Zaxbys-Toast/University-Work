require_relative "hand_identifier"

class HandSorter
    def self.sort_hands(hands)
        sort_hands_by_type(hands)
        sort_ties(hands)
    end

    def self.sort_hands_by_type(hands)
      hands.sort!{ |h1, h2| h1.get_type <=> h2.get_type}.reverse!
    end

    # Splits hands into subarrays of similar types and calls for them to be appropriately sorted
    def self.sort_ties(hands)
      start_index = 0
      last_type = hands[0].get_type

      hands.each_with_index do |hand, i|
        if hand.get_type != last_type
          hands[start_index..i-1] = sort_subarray(hands[start_index..i-1])

          start_index = i
          last_type = hand.get_type
        elsif i == hands.size - 1
          hands[start_index..i] = sort_subarray(hands[start_index..i])
        end
      end
    end

    def self.sort_subarray(hands)
      hand_type = hands[0].get_type

      if hand_type == 9
        hands.sort! { |h1, h2| compare_royal_flush(h1, h2) }.reverse!
      elsif hand_type == 8
        hands.sort! { |h1, h2| compare_straight_flush(h1, h2) }.reverse!
      elsif hand_type == 7
        hands.sort! { |h1, h2| compare_four_of_a_kind(h1, h2) }.reverse!
      elsif hand_type == 6
        hands.sort! { |h1, h2| compare_full_house(h1, h2) }.reverse!
      elsif hand_type == 5
        hands.sort! { |h1, h2| compare_flush(h1, h2) }.reverse!
      elsif hand_type == 4
        hands.sort! { |h1, h2| compare_straight(h1, h2) }.reverse!
      elsif hand_type == 3
        hands.sort! { |h1, h2| compare_three_of_a_kind(h1, h2) }.reverse!
      elsif hand_type == 2
        hands.sort! { |h1, h2| compare_two_pair(h1, h2) }.reverse!
      elsif hand_type == 1
        hands.sort! { |h1, h2| compare_pair(h1, h2) }.reverse!
      else
	hands.sort!  { |h1, h2| compare_high_card(h1, h2) }.reverse!
      end

      return hands
    end


    # =============== Comparators ===============
    # All return:
    #  -1 if first hand is weaker
    #   1 if first hand is stronger

    def self.compare_royal_flush(h1, h2)
      if h1.get_sorted_cards()[0].get_suit < h2.get_sorted_cards()[0].get_suit
        return -1
      end

      return 1
    end

    def self.compare_straight(h1, h2)
      l1 = h1.get_sorted_cards()
      l2 = h2.get_sorted_cards()

      highest_card_comparison = compare_highest_card(l1, l2)

      if highest_card_comparison != 0
        return highest_card_comparison
      end

      highest_card_suit1 = -1
      highest_card_suit2 = -1

      if !HandIdentifier.is_royal_straight(l1)
        highest_card_suit1 = l1[l1.length - 1].suit
      else
        highest_card_suit1 = l1[0].suit
      end

      if !HandIdentifier.is_royal_straight(l2)
        highest_card_suit2 = l2[l2.length - 1].suit
      else
        highest_card_suit2 = l2[0].suit
      end

      if highest_card_suit1 < highest_card_suit2
        return -1
      end

      return 1
    end

    def self.compare_straight_flush(h1, h2)
      l1 = h1.get_sorted_cards()
      l2 = h2.get_sorted_cards()

      highest_card_comparison = compare_highest_card(l1, l2)

      if highest_card_comparison != 0
	return highest_card_comparison
      end

      if l1[0].get_suit < l2[0].get_suit
	return -1
      end

      return 1
    end

    def self.compare_four_of_a_kind(h1, h2)
      c1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 4)[0]
      c2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 4)[0]

      value1 = c1.get_value()
      value2 = c2.get_value()

      if c1.get_value() == 0
	value1 = 13
      end

      if c2.get_value() == 0
	value2 = 13
      end

      if value1 < value2
	return -1
      end

      return 1
    end

    def self.compare_full_house(h1, h2)
      c1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 3)[0]
      c2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 3)[0]

      value1 = c1.get_value()
      value2 = c2.get_value()

      if c1.get_value() == 0
        value1 = 13
      end

      if c2.get_value() == 0
        value2 = 13
      end

      if value1 < value2
        return -1
      end

      return 1
    end

    def self.compare_flush(h1, h2)
      l1 = h1.get_sorted_cards()
      l2 = h2.get_sorted_cards()

      highest_card_comparison = compare_highest_card(l1, l2)

      if highest_card_comparison != 0
        return highest_card_comparison
      end

      if l1[0].get_suit < l2[0].get_suit
        return -1
      end

      return 1
    end

    def self.compare_three_of_a_kind(h1, h2)
      c1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 3)[0]
      c2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 3)[0]

      value1 = c1.get_value()
      value2 = c2.get_value()

      if c1.get_value() == 0
        value1 = 13
      end

      if c2.get_value() == 0
        value2 = 13
      end

      if value1 < value2
        return -1
      end

      return 1
    end

    def self.compare_two_pair(h1, h2)
      pairs1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 2)
      pairs2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 2)

      highest_card_comparison = compare_highest_card(pairs1, pairs2)

      if highest_card_comparison != 0
	return highest_card_comparison
      end

      kicker1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 1)
      kicker2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 1)

      kicker_card_comparison = compare_highest_card(kicker1, kicker2)

      if kicker_card_comparison != 0
	return kicker_card_comparison
      end

      kicker_card1 = kicker1[0]
      kicker_card2 = kicker2[0]

      if kicker_card1.get_suit < kicker_card2.get_suit
	return -1
      end

      return 1 
    end

    def self.compare_pair(h1, h2)
      pairs1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 2)
      pairs2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 2)

      highest_card_comparison = compare_highest_card(pairs1, pairs2)

      if highest_card_comparison != 0
        return highest_card_comparison
      end

      singles1 = get_cards_occuring_n_times(h1.get_sorted_cards(), 1)
      singles2 = get_cards_occuring_n_times(h2.get_sorted_cards(), 1)

      highest_single_comparison = compare_highest_card(singles1, singles2)

      if highest_single_comparison != 0
	return highest_single_comparison
      end

      highest_single1 = singles1.max_by { |card| card.get_value }
      highest_single2 = singles2.max_by { |card| card.get_value }

      if singles1.min_by { |card| card.get_value() }.get_value() == 0
        highest_single1 = singles1.min_by { |card| card.get_value() }
      end

      if singles2.min_by { |card| card.get_value() }.get_value() == 0
        highest_single2 = singles2.min_by { |card| card.get_value() }
      end

      if highest_single1.get_suit < highest_single2.get_suit
        return -1
      end

      return 1
    end

    def self.compare_high_card(h1, h2)
      l1 = h1.get_sorted_cards()
      l2 = h2.get_sorted_cards()

      highest_card_comparison = compare_highest_card(l1, l2)

      if highest_card_comparison != 0
	return highest_card_comparison
      end

      highest_card1 = l1.max_by { |card| card.get_value() }
      highest_card2 = l2.max_by { |card| card.get_value() }

      if l1.min_by { |card| card.get_value() }.get_value() == 0
	highest_card1 = l1.min_by { |card| card.get_value() }
      end

      if l2.min_by { |card| card.get_value() }.get_value() == 0
	highest_card2 = l2.min_by { |card| card.get_value() }
      end

      if highest_card1.get_suit() < highest_card2.get_suit()
	return -1
      end

      return 1
    end

    # =============== Helpers ===============
    
    # Method that compares highest cards of two sorted card lists of same type
    # Returns:
    #  -1 if first hand is weaker
    #   1 if first hand is stronger
    #   0 if both hands are tied
    def self.compare_highest_card(l1, l2)
      value_list1 = []
      value_list2 = []
    
      l1.zip(l2).each do |card1, card2|
        if card1.get_value == 0
          if l1.length == Hand::HAND_SIZE
            if HandIdentifier.is_straight(l1) and !HandIdentifier.is_royal_straight(l1)
              value_list1 << 0
            else
              value_list1 << 13
            end
          else
            value_list1 << 13
          end
        else
          value_list1 << card1.get_value
        end

        if card2.get_value == 0
          if l2.length == Hand::HAND_SIZE
            if HandIdentifier.is_straight(l2) and !HandIdentifier.is_royal_straight(l2)
              value_list2 << 0
            else
              value_list2 << 13
            end
          else
            value_list2 << 13
          end
        else
          value_list2 << card2.get_value
        end

      end

      value_list1.sort!.reverse!
      value_list2.sort!.reverse!

      value_list1.zip(value_list2).each do |value1, value2|
        if value1 < value2
          return -1
        elsif value1 > value2
          return 1
        end
      end

      return 0
    end

    # Given a sorted card list, this method returns a list of cards which appear n times in the list
    def self.get_cards_occuring_n_times(card_list, n)
      result = []

      card_list.each do |card|
        if !result.include?(card)
          if card_list.count(card) == n
            result << card
          end
        end
      end

      return result
    end

end
