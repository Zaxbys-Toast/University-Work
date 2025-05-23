# Deck Julia Class
using Random
include("Card.jl")

mutable struct Deck
	cards::Vector{Card}
	
	function Deck()
		suits = ["S","H","C","D"]
		ranks = ["A","2","3","4","5","6","7","8","9","10","J","Q","K"]
		deck = [Card(rank, suit) for rank in ranks, suit in suits]
		deck = vec(deck)
		# Shuffle the deck as soon as it is created. Eliminates the need for two functions
		shuffle!(deck)
		new(deck)
	end
end

function deal(deck::Deck)
	return pop!(deck.cards)
end

function printDeck(deck::Deck)
	i::Int = 0
	for card in reverse(deck.cards)
		print(card, " ")
		i += 1
		if ( i % 13 == 0 )
			println()
		end
	end
	println()
end

function deal_card!(deck::Deck)
    return pop!(deck.cards)
end
