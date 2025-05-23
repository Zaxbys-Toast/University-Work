# Imports from our other files
include("Card.jl")
include("Deck.jl")
include("Hand.jl")
include("HandIdentifier.jl")
include("HandSorter.jl")


function main()
    is_testing = length(ARGS) > 0  # Enter testing mode if an argument is passed
    num_hands = 6  # Declare number of hands


    println("*** P O K E R H A N D A N A L Y Z E R ***\n")

    if is_testing  # Enter testing mode
	hands = Hand[]
        file_path = ARGS[1]
        print_file(file_path)
        deal_from_file(file_path, hands)

        if has_duplicate(hands)
            return  # Exit program if a duplicate is found
        end

        print_hands(hands)  # Print hands from test file
        assign_types(hands)
        print_ranked_hands(hands)
    else
    	hands = [Hand() for _ in 1:num_hands]  # Create 6 new Hand instances
        deck = Deck()
        printDeck(deck)
        deal_from_deck(hands, deck)
        print_hands(hands)
        print_remaining_deck(deck)
        assign_types(hands)
        print_ranked_hands(hands)
    end
end

function print_file(path)
    println("*** USING TEST DECK ***")
    println("\n*** File: $path\n")

    open(path, "r") do f  # Reading test file
        println(read(f, String))
    end
end


function deal_from_file(filename::String, hands::Vector{Hand})
    open(filename, "r") do file
        for line in eachline(file)
            line = strip(line)
            cards = split(line, ",")
            hand = Hand()
            
            for card_str in cards
                card_str = strip(card_str)
                rank = string(card_str[1:end-1])
		suit = string(card_str[end])
                card = Card(rank,suit)
                add_card!(hand, card)
            end
            
            push!(hands, hand)
        end
    end
end

function has_duplicate(hands::Vector{Hand})
    for hand in hands
        seen = Set()
        for card in hand.cards
            if in(card, seen)
                return true
            end
            push!(seen, card)
        end
    end
    return false
end

function print_hands(hands)
    println("\n*** Here are the six hands...")
    for hand in hands
        sorted_cards = sort(hand.cards, by = card -> (get_value(card), get_suit(card)))
        println(join([to_string(card) for card in sorted_cards], " "))
    end
    println()
end

function assign_types(hands)
    for hand in hands
        assign_type!(hand)
    end

    hands_sorted = sort_hands!(hands)
    return hands_sorted
end

function print_ranked_hands(hands)
    sorted_hands = sort(hands, by = hand -> -get_type(hand))
    sort_hands!(sorted_hands)
    println("--- WINNING HAND ORDER ---")

    for hand in sorted_hands
        hand_string = join([to_string(card) for card in hand.cards], " ")
        println("$hand_string - $(HAND_MAP[get_type(hand) + 1])")
    end
end

function print_deck(deck)
    println("*** USING RANDOMIZED DECK OF CARDS ***\n")
    println("*** Shuffled 52 card deck:")
    println(deck_to_string(deck))
end

function deal_from_deck(hands, deck)
    for _ in 1:5
        for hand in hands
            add_card!(hand, deal_card!(deck))
        end
    end
end

function print_remaining_deck(deck)
    println("*** Here is what remains in the deck...")
    printDeck(deck)
    println()
end

# Run the main program
if abspath(PROGRAM_FILE) == @__FILE__
    main()
end

