class Hand

  #define the number of cards per hand and the different hand types
  HAND_SIZE = 5
    HAND_MAP = ['High Card', 'Pair', 'Two Pair', 'Three of a Kind', 'Straight',
                'Flush', 'Full House', 'Four of a Kind', 'Straight Flush', 'Royal Straight Flush']
  attr_accessor :cards  
  #constructor to initialize the cards and hand type
    def initialize
      @cards = []
      @type = -1
    end
  
    def to_s #string representation of the hand object
      result = ''
      @cards.each do |card|
        result += card.to_s
      end
      return result
    end
  
    def add_card(card)
      @cards << card
      return nil
    end
  
    def get_type
      return @type
    end
  
    def set_type(t)
      @type = t 
      return nil 
    end
  
    def get_cards
      return @cards
    end

    def get_sorted_cards
     @cards.sort_by { |card| card.get_value }
    end
  end
