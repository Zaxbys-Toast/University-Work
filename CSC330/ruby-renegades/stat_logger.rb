class StatLogger
  # Defines the types of poker hands for tracking statistics
  # Ordered from best to worst to match display order
  HAND_TYPES = [
    'ROYAL STRAIGHT FLUSH', # 9
    'STRAIGHT FLUSH',       # 8
    'FOUR OF A KIND',       # 7
    'FULL HOUSE',          # 6
    'FLUSH',               # 5
    'STRAIGHT',            # 4
    'THREE OF A KIND',      # 3
    'TWO PAIR',            # 2
    'PAIR',                # 1
    'HIGH CARD'            # 0
  ]

  def initialize
    @hand_counts = Array.new(HAND_TYPES.length, 0)
    @total_hands = 0
  end

  def log_hands(hands)
    hands.each do |hand|
      hand_type = hand.get_type
      if hand_type.is_a?(Integer) && hand_type >= 0 && hand_type < HAND_TYPES.length
        @hand_counts[9 - hand_type] += 1  # Convert the type to our array index
        @total_hands += 1
      end
    end
  end

  def hand_counts
    @hand_counts
  end

  def print_stats
    puts "---- STATISTICAL ANALYSIS ----"
    HAND_TYPES.each_with_index do |type, i|
      puts "#{type} #{@hand_counts[i]}"
    end
  end
end
