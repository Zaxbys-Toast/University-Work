class AssignType1Joker
    def self.assign_type_1_joker(hand)
        cards = hand.get_sorted_cards

        if can_be_royal_straight_flush(cards)
            hand.set_type(9)
            assign_joker_value_to_royal_straight_flush(hand)
        elsif can_be_straight_flush(cards)
            hand.set_type(8)
            assign_joker_value_to_straight_flush(hand)
        elsif can_be_four_of_a_kind(cards)
            hand.set_type(7)
            assign_joker_value_to_four_of_a_kind(hand)
	elsif can_be_full_house(cards)
        # Assign three of a kind logic works here as well
	    hand.set_type(6)
	    assign_joker_value_to_three_of_a_kind(hand)
        elsif can_be_flush(cards)
            hand.set_type(5)
            assign_joker_value_to_flush(hand)
        elsif can_be_straight(cards)
            hand.set_type(4)
            assign_joker_value_to_straight(hand)
        elsif can_be_three_of_a_kind(cards)
            hand.set_type(3)
            assign_joker_value_to_three_of_a_kind(hand)
        # Not checking for two pair because if it can be a two pair, it can be a three of a kind
        else
          # It can always be a pair
            hand.set_type(1)
            assign_joker_value_to_pair(hand)
        end
    end

    def self.can_be_royal_straight_flush(cards)
      cards_without_joker = get_list_without_joker(cards)

      if not four_cards_are_flush(cards_without_joker)
        return false
      end

      # A, 10, J, Q
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 10 and
          cards_without_joker[3].get_value == 11 
          return true
      end

       # A, 10, J, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 10 and
          cards_without_joker[3].get_value == 12 
          return true
      end     

       # A, 10, Q, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12 
          return true
      end    

       # A, J, Q, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 10 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12 
          return true
      end  

       # 10, J, Q, K
      if cards_without_joker[0].get_value == 9 and
          cards_without_joker[1].get_value == 10 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12 
          return true
      end  

      false
    end

    def self.can_be_straight_flush(cards)
      cards_without_joker = get_list_without_joker(cards)

      if four_cards_are_flush(cards_without_joker) and can_be_straight(cards)
        return true
      end

      false
    end

    def self.can_be_four_of_a_kind(cards)
      cards_without_joker = get_list_without_joker(cards)

      frequency_set = get_frequency_set(cards_without_joker) 

      frequency_set.each do |value|
        if value == 3 or value == 4
          return true
        end
      end

      false
    end

    def self.can_be_full_house(cards)
      cards_without_joker = get_list_without_joker(cards)

      frequency_set = get_frequency_set(cards_without_joker)
      
      frequency_set == [2,2]
    end

    def self.can_be_flush(cards)
      cards_without_joker = get_list_without_joker(cards)

      if four_cards_are_flush(cards_without_joker)
        return true
      end

      false
    end

    def self.can_be_straight(cards)
      cards_without_joker = get_list_without_joker(cards)
      gap_found = false
      prev_value = cards_without_joker[0].get_value - 1
      # Check for royal straights
      # A, 10, J, Q
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 10 and
          cards_without_joker[3].get_value == 11
          return true
      end

       # A, 10, J, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 10 and
          cards_without_joker[3].get_value == 12
          return true
      end

       # A, 10, Q, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 9 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12
          return true
      end

       # A, J, Q, K
      if cards_without_joker[0].get_value == 0 and
          cards_without_joker[1].get_value == 10 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12
          return true
      end

       # 10, J, Q, K
      if cards_without_joker[0].get_value == 9 and
          cards_without_joker[1].get_value == 10 and
          cards_without_joker[2].get_value == 11 and
          cards_without_joker[3].get_value == 12
          return true
      end
	
      cards_without_joker.each do |card|
        curr_value = card.get_value
        if curr_value != prev_value + 1
          if curr_value != prev_value + 2
            return false
          else
            if gap_found
              return false
            else
              gap_found = true
            end
          end
        end

        prev_value = curr_value
      end 

      true
    end

    def self.can_be_three_of_a_kind(cards)
      cards_without_joker = get_list_without_joker(cards)

      frequency_set = get_frequency_set(cards_without_joker) 

      frequency_set.each do |value|
        if value == 2
          return true
        end
      end

      false
    end


    # =============== Type Checkers ===============
    # All expect a card list of length 4, excluding the joker
    
    def self.four_cards_are_flush(cards)
        prev_suit = cards[0].get_suit

        cards.all? do |card|
            if card.get_suit != prev_suit
                return false
            end
            prev_suit = card.get_suit
        end
        true
    end

    def self.four_cards_are_straight(cards)
        prev_value = cards[0].get_value - 1
        
        cards.each do |card|
            curr_value = card.get_value
            return false if curr_value != prev_value + 1
            prev_value = curr_value
        end 
        true
    end

    # =============== Helpers ===============
     
    # Expects a list of cards that contains one joker card
    # Returns a list of cards without joker sorted ascending by card value
    def self.get_list_without_joker(cards)
      # Deep copies the list so as not to modify the original
      copied_list = Marshal.load(Marshal.dump(cards))

      joker_ind = -1

      copied_list.each_with_index do |card, index|
        if card.get_value == -1 # TODO: Change this to card.is_joker as soon as that is implemented
          joker_ind = index
          break
        end
      end

      copied_list.delete_at(joker_ind)
      copied_list.sort_by { |card| card.get_value }
    end

    def self.get_frequency_set(cards)
      set = []

      prev_value = -1

      cards.each do |card|
        if card.get_value == prev_value
          next
        end

        set << cards.count(card)
        prev_value = card.get_value
      end

      return set.sort
    end

    def self.get_joker_index(cards)
      cards.each_with_index do |card, index|
        return index if card.get_value == -1
      end
      -1 # Shouldn't happen if input is correct
    end
    
    def self.get_cards_occuring_n_times_with_missing_suit(card_list, n)
      value_count = Hash.new(0)
      suit_groups = Hash.new { |h, k| h[k] = [] }

      card_list.each do |card|
        value = card.get_value
        suit = card.get_suit
        value_count[value] += 1
        suit_groups[value] << suit
      end

      values_with_n = value_count.select { |_, count| count == n }
      return nil if values_with_n.empty? 

      max_value = values_with_n.keys.max_by { |value| value == 0 ? Float::INFINITY : value }
      suits = suit_groups[max_value]

      all_suits = (0..3).to_a 
      missing_suits = all_suits - suits
      max_missing_suit = missing_suits.max

      [max_value, max_missing_suit] 
    end
    # =============== Assigners ===============
   
    def self.assign_joker_value_to_royal_straight_flush(hand)
	unsorted_cards = hand.get_cards
	joker_ind = get_joker_index(unsorted_cards)
	cards = hand.get_sorted_cards
	common_suit = cards[2].get_suit
	if cards[1].get_value != 0
	  unsorted_cards[joker_ind].value = 0
	  unsorted_cards[joker_ind].suit = common_suit
	elsif cards[2].get_value != 9
	  unsorted_cards[joker_ind].value = 9
          unsorted_cards[joker_ind].suit = common_suit
        elsif cards[3].get_value != (10)
	  unsorted_cards[joker_ind].value = 10
          unsorted_cards[joker_ind].suit = common_suit
	elsif cards[4].get_value != (11)
	  unsorted_cards[joker_ind].value = 11
          unsorted_cards[joker_ind].suit = common_suit
	else
	  unsorted_cards[joker_ind].value = 12
          unsorted_cards[joker_ind].suit = common_suit
	end
    end

    def self.assign_joker_value_to_straight_flush(hand)
	# Same as above
      unsorted_cards = hand.get_cards
      joker_ind = get_joker_index(unsorted_cards)
      cards = get_list_without_joker(unsorted_cards)
      prev_value = cards[0].get_value - 1

      cards.each do |card|
        curr_value = card.get_value
        if curr_value != prev_value + 1
          if can_be_straight_flush(cards)
            #card = Card.new(pre_value + 1, card.get_suit)
            hand.get_cards[joker_ind].value = prev_value + 1
            hand.get_cards[joker_ind].suit = card.get_suit
            #return card
          end
          #card = Card.new(prev_Value + 1, 3)
          hand.get_cards[joker_ind].value = prev_value + 1
          hand.get_cards[joker_ind].suit = card.get_suit
          #return card
        end
        prev_value = curr_value
      end
      if hand.get_cards[0].get_value == -1
        if can_be_straight_flush(cards)
          #card = Card.new(cards[0].get_value - 1, cards[0].get_suit)
          hand.get_cards[joker_ind].value = cards[0].get_value - 1
          hand.get_cards[joker_ind].suit = cards[0].get_suit
        else
          #card = Card.new(cards[0].get_value - 1, 3)
          hand.get_cards[joker_ind].value = cards[0].get_value - 1
          hand.get_cards[joker_ind].suit = 3
        end
      end

    end

    def self.assign_joker_value_to_four_of_a_kind(hand)
	# Find the 3 of a kind value and missing suit
	cards = hand.get_cards
      	i, j = get_cards_occuring_n_times_with_missing_suit(cards, 3)
	joker_ind = get_joker_index(cards)
	hand.get_cards[joker_ind].value = i
	hand.get_cards[joker_ind].suit = j  
    end

    def self.assign_joker_value_to_flush(hand)
 	# Find the highest card left in the suit
 	unsorted_cards = hand.get_cards
	cards = get_list_without_joker(unsorted_cards) 
	joker_ind = get_joker_index(unsorted_cards)
	
	if cards[0].get_value != 0 
	  hand.get_cards[joker_ind].value = 0
	  hand.get_cards[joker_ind].suit = cards[0].get_suit
	elsif cards[3].get_value != 12
	  hand.get_cards[joker_ind].value = 12
	  hand.get_cards[joker_ind].suit = cards[0].get_suit
	elsif cards[2].get_value != 11
	  hand.get_cards[joker_ind].value = 11
	  hand.get_cards[joker_ind].suit = cards[0].get_suit
	else
	  hand.get_cards[joker_ind].value = 10
	  hand.get_cards[joker_ind].suit = cards[0].get_suit
	end
    end

    def self.assign_joker_value_to_straight(hand)
      unsorted_cards = hand.get_cards
      joker_ind = get_joker_index(unsorted_cards)
      cards = get_list_without_joker(unsorted_cards)
      prev_value = cards[0].get_value - 1
      
      if cards[0].get_value == 0 and cards[3].get_value == 11
	if cards[0].get_value != 0
          hand.get_cards[joker_ind].value = 0
          hand.get_cards[joker_ind].suit = 3
        elsif cards[1].get_value != 9
          hand.get_cards[joker_ind].value = 9
          hand.get_cards[joker_ind].suit = 3
        elsif cards[2].get_value != (10)
          hand.get_cards[joker_ind].value = 10
          hand.get_cards[joker_ind].suit = 3
        elsif cards[3].get_value != (11)
          hand.get_cards[joker_ind].value = 11
          hand.get_cards[joker_ind].suit = 3
        else
          hand.get_cards[joker_ind].value = 12
          hand.get_cards[joker_ind].suit = 3
        end

      else
        cards.each do |card|
          curr_value = card.get_value
          if curr_value != prev_value + 1
            hand.get_cards[joker_ind].value = prev_value + 1
            hand.get_cards[joker_ind].suit = card.get_suit
          end
          prev_value = curr_value
        end
        if hand.get_sorted_cards[0].get_value == -1
	  if cards[3].get_value != 12
            hand.get_cards[joker_ind].value = cards[3].get_value + 1
            hand.get_cards[joker_ind].suit = 3
          else
            hand.get_cards[joker_ind].value = cards[0].get_value - 1
            hand.get_cards[joker_ind].suit = 3
	  end
        end
      end
    end
    def self.assign_joker_value_to_three_of_a_kind(hand)
        # Find the highest pair
        i, j = get_cards_occuring_n_times_with_missing_suit(hand.get_cards, 2)
        joker_ind = get_joker_index(hand.get_cards)
        hand.get_cards[joker_ind].value = i
        hand.get_cards[joker_ind].suit = j
    end

    def self.assign_joker_value_to_pair(hand)
        # Find the highest card value
        cards = get_list_without_joker(hand.get_cards)
	joker_ind = get_joker_index(hand.get_cards)
	suit = 3
	if cards[0].get_value != 0
	  hand.get_cards[joker_ind].value = cards[3].get_value
	  if cards[3].get_suit == 3
	   hand.get_cards[joker_ind].suit = 2
	  else   
	    hand.get_cards[joker_ind].suit = 3
          end
	else
	  hand.get_cards[joker_ind].value = 0
          if cards[0].get_suit == 3
            hand.get_cards[joker_ind].suit = 2
          else
	    hand.get_cards[joker_ind].suit = 3
	  end
        end
    end
end

