require_relative 'card'
require_relative 'hand'
require_relative 'assign_type_2_joker'

hand = Hand.new

hand.add_card(Card.new("10H"))
hand.add_card(Card.new("XR"))
hand.add_card(Card.new("AC"))
hand.add_card(Card.new("JC"))
hand.add_card(Card.new("XB"))

AssignType2Joker.assign_type_2_jokers(hand)

hand.get_sorted_cards.each do | card |

        puts card.get_value

end

