# Imports from our other files
require_relative 'card'
require_relative 'deck'
require_relative 'hand'
require_relative 'hand_identifier'
require_relative 'hand_sorter'
require_relative 'stat_logger'

def main
#  is_testing = ARGV.length > 0 # Enter testing mode if main has passed an argument
  is_testing = false # going to then check for '-f' later on
  include_jokers = false
  collect_stats = false # Initialize collections flag for "-s" if in argument
  num_hands = 6 # Declare number of hands
  hands = [] # Array for hands

  num_hands.times do # Create 6 new arrays of hands
    hands << Hand.new
  end

  puts "*** P O K E R H A N D A N A L Y Z E R ***\n\n"
  puts "\n"                                                     #Spacing

#  if is_testing # Enter testing mode
  if ARGV.include?('-f')
    is_testing = true # file input flag
    f_mark = ARGV.index('-f')
    if f_mark + 1 < ARGV.length # checks if there is another arg
       file_path = ARGV[f_mark + 1]
    else
       puts "Error: NO file specified after -f flag"
       return
    end
  end

  if ARGV.include?('-j')
    include_jokers = true
    j_mark = ARGV.index('-j')
    if j_mark + 1 < ARGV.length && ARGV[j_mark + 1] =~ /^\d+$/
      num_samples = ARGV[j_mark + 1].to_i
    end
  end

  if ARGV.include?('-s')
    collect_stats = true # Statistics collection flag
    s_mark = ARGV.index('-s')
    if s_mark + 1 < ARGV.length && ARGV[s_mark + 1] =~ /^\d+$/
      num_samples = ARGV[s_mark + 1].to_i
    else
      num_samples = 1000
    end
  end

  if ARGV.include?('-s') && ARGV.include?('-j')
    collect_stats = true
    include_jokers = true
    if s_mark + 1 < ARGV.length && ARGV[s_mark + 1] =~ /^\d+$/
      num_samples = ARGV[s_mark + 1].to_i
    elsif j_mark + 1 < ARGV.length && ARGV[j_mark + 1] =~ /^\d+$/
      num_samples = ARGV[j_mark + 1].to_i
    end
  end

  if is_testing # Testing mode: read from file
    print_file(file_path)
    deal_from_file(hands, file_path)

    if has_duplicate(hands)
      return # Exit program if a duplicate is found
    end

    print_hands(hands) # Print hands from test file
    assign_types(hands)
    print_ranked_hands(hands)
  elsif collect_stats # Statistics collection mode
    stat_logger = StatLogger.new # Initialize the stat logger

    num_samples.times do
      hands = []
      num_hands.times do
        hands << Hand.new
      end

      deck = Deck.new(include_jokers)
      deck.shuffle # Ensure the deck is shuffled before dealing
      deal_from_deck(hands, deck)
      assign_types(hands)
      stat_logger.log_hands(hands) # Log the hand types for statistics
    end

    puts "---- STATISTICAL ANALYSIS ----"
    StatLogger::HAND_TYPES.each_with_index do |hand_type, index|
      puts "#{hand_type.ljust(24)} #{stat_logger.hand_counts[index]}"
    end

  else
    # Methods for handling our cards
    deck = Deck.new(include_jokers)
    print_deck(deck)
    deal_from_deck(hands, deck)
    print_hands(hands)
    print_remaining_deck(deck)
    assign_types(hands)
    print_ranked_hands(hands)
  end
end

#=============== Testing functions ===============
def print_file(path)
  puts "*** USING TEST DECK ***\n"
  puts "\n*** File: #{path}\n"

  File.open(path, 'r') do |f| # Reading our testfile
    puts f.read
  end
end

def deal_from_file(hands, path) # Printing each hand from our testfile
  File.open(path, 'r') do |f|
    f.each_with_index do |line, i|
      line.split(',').each do |token|
        hands[i].add_card(Card.new(token.strip))
      end
    end
  end
end

def has_duplicate(hands)
  card_hashes = [] # Array to store hash values for the cards

  # Iterate through each hand and iterate through each hands cards
  hands.each do |hand|
    sorted_cards = hand.instance_variable_get(:@cards).sort_by { |card| [card.get_value, card.get_suit] }
    sorted_cards.each do |card|
      card_hash = card.get_value * 10 + card.get_suit

      # Checks if the card has already existed and if so then we print an error and the duplicated card
      if card_hashes.include?(card_hash)
        puts "\n*** ERROR - DUPLICATED CARD FOUND IN DECK ***\n"
        puts "\n*** Duplicate: #{card.to_string.strip} ***"
        return true
      else
        # Adds unique card to array
        card_hashes << card_hash
      end
    end
  end

  false
end

#=============== Common functions ===============
# Print the distributed hands
def print_hands(hands)
  puts "\n*** Here are the six hands..."
  hands.each do |hand|
    puts hand.cards.map { |card| card.to_string.strip }.join(' ')
  end
  puts
end

def assign_types(hands)

  hands.each do |hand|

        HandIdentifier.assign_type(hand)

  end

  hands_sorted = HandSorter.sort_hands(hands)
  return hands_sorted
end

def print_ranked_hands(hands)
  sorted_hands = hands.sort_by { |hand| -hand.get_type }
  puts "--- WINNING HAND ORDER ---"                             #Print out header for winning hands
  hand_strings = sorted_hands.map do |hand|                     #Loop through each sorted hand
        hand.instance_variable_get(:@cards).map { |card| card.to_string.strip }.join(' ')
  end
  max_hand_length = hand_strings.map(&:length).max              #Determine the maximum length within the hands
  sorted_hands.each_with_index do |hand, index|                 #And use this to align the printout of each hand
        hand_string = hand_strings[index]
        hand_type = Hand::HAND_MAP[hand.get_type]
        puts "#{hand_string.ljust(max_hand_length)} - #{hand_type}"
  end
end


#=============== Non-testing Functions ==========

def print_deck(deck)

        puts "*** USING RANDOMIZED DECK OF CARDS ***"
        puts
        puts "*** Shuffled 52 card deck:"
        puts deck.to_string

end

def deal_from_deck(hands, deck)

        (0...Hand::HAND_SIZE).each do |i|

                hands.each do |hand|

                        hand.add_card(deck.deal_card)

                end

        end

end

def print_remaining_deck(deck)
  remaining_cards = deck.instance_variable_get(:@cards) #Retrieve the remaining cards in the deck at this current state
  remaining_cards_strings = remaining_cards.map { |card| card.to_string.strip }         #Represent each card as a string
  puts "*** Here is what remains in the deck..."
  puts remaining_cards_strings.join(' ')                        #Join the cards with a space to print everything out on one line
  puts
end

# Run the main program
main if __FILE__ == $PROGRAM_NAME
