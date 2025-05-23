class Card                      #Map the ranks and suits
  VALUE_MAP = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
  SUIT_MAP = ['D', 'C', 'H', 'S']

  class << self
    def get_value_index(value)  #Find the index of a value (rank) in the map
      VALUE_MAP.index(value)
    end

    def get_suit_index(suit)    #Find the index of a suit in the map
      SUIT_MAP.index(suit)
    end
  end

  #Update from reader to accessor so that the cards are not read only; to prevent potential conflicts when changing cards w/
  #...jokers   
  attr_accessor :value, :suit, :is_joker, :is_red_joker  #Define the attributes for value, suit, and jokers

  def initialize(*args)         #Initialize a card with either two arguments for value & suit or one single string
    @is_joker = false           #Joker flag, set to  false by default
    @is_red_joker = false       #Red joker flag, set to false by default
    case args.length
    when 2
      value_input = args[0]     #If it's two arguments, directly assign the value and suit
      suit_input = args[1]
      if value_input == "XR" || value_input == "XB"  #Check if the card is a joker
        @is_joker = true        #If it is, the joker flag becomes true
        @is_red_joker = (value_input == "XR")   #Set the red joker depending on if the joker is red
        @value = -1             #Then assign values of -1 for these jokers
        @suit = -1
      else			#For regular/non-joker cards...
        @value = value_input    #Assign the provided value
        @suit = suit_input      #Assign the provided suit
      end

    when 1                      #If it's one argument, parse to get the value and suit
      string = args[0].strip
      if string == "XR" || string == "XB"       #Check if the card passed in is a joker
        @is_joker = true                        #If it is, mark the joker flag as true
        @is_red_joker = (string == "XR")        #Based on the color of the joker, set the red joker flag
        @value = -1                             #And assign values of -1 to represent jokers
        @suit = -1
      else
        value_string = string[0..-2]            #Pull out the rank
        suit_string = string[-1]                #Then pull out the suit
        @value = Card.get_value_index(value_string)             #Retrieve the rank index
        @suit = Card.get_suit_index(suit_string)                #Retrieve the suit index
      end

    else
      raise ArgumentError, "Invalid number of arguments received!"
    end
  end

  def <(other)                  #Compare two cards' values
    self.get_value < other.get_value
  end

  def ==(other)                 #Check if two cards are equal in rank
    self.get_value == other.get_value
  end

  def to_string(print_width=4)  #Return the card as a string
    if @is_joker                #Use the joker flag to check if card is a joker. If so,  print out XR or XB depending on the color
      joker_string = @is_red_joker ? "XR" : "XB"
      card_string = joker_string
    else
      card_string = "#{VALUE_MAP[@value]}#{SUIT_MAP[@suit]}"    #For other cards, represent them with their value & suit symbols
    end
    card_string.ljust(print_width)
  end

  def represent                 #Return the representation of the card
    "#{self.class}(value=#{get_value}, suit=#{get_suit})"
  end

  def get_value                 #Getter for the card's value
    @value
  end

  def get_suit                  #Getter for the card's suit
    @suit
  end
  
  def get_cards
    @cards
  end
end


