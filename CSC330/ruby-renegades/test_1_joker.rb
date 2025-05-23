require_relative 'card'
require_relative 'hand'
require_relative 'hand_identifier'
require_relative 'assign_type_1_joker'

hand = Hand.new

hand.add_card(Card.new("9H"))
hand.add_card(Card.new("6C"))
hand.add_card(Card.new("4H"))
hand.add_card(Card.new("7H"))
hand.add_card(Card.new("XR"))
#AssignType1Joker.assign_type_1_joker(hand)

AssignType1Joker.assign_type_1_joker(hand)

puts hand.get_type
hand.get_cards.each do |card|
  puts card.get_value
end
