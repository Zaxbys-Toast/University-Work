require_relative 'card'

class Deck
  NUM_CARDS = 52
  CARDS_PER_LINE = 13  # Number of cards to display per line when printing

  def initialize(joker_bool = false)  #Joker boolean, this will decide if jokers are put into the deck
    
    @cards = []
    NUM_CARDS.times do |i|
      value = i % 13       # Card values from 0 to 12
      suit = (i / 13).to_i # Suits from 0 to 3
      @cards << Card.new(value, suit)
    end
    if joker_bool
      @cards << Card.new("XR")
      @cards << Card.new("XB")
    end
    shuffle
  end

  def shuffle
    @cards.shuffle!
  end

  def deal_card
    @cards.shift
  end

  def to_string
    result = ''
    @cards.each_with_index do |card, i|
      result += card.to_string
      result += "\n" if (i + 1) % CARDS_PER_LINE == 0
    end
    result
  end

  def represent
    @cards.map(&:represent).join("\n")
  end
end
