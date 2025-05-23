#!/usr/bin/perl
use warnings;

use lib '.';  # Assuming Card.pm, Deck.pm, and Hand.pm are in the same directory
use Card;
use Deck;
use Hand;
use HandIdentifier;
use HandSorter;
# ================ Helper ===================
# Initialize an array to track dealt cards (52 cards: 13 ranks * 4 suits)
my @dealt_cards = (0) x 52;  # 0 means card has not been dealt

# A helper subroutine to check for duplicates
sub check_for_duplicates {
    my ($card) = @_;
    
    # Use the card's rank and suit integer values directly
    my $rank_value = $card->{rank};  # Rank is already an integer
    my $suit_value = $card->{suit};  # Suit is already an integer
    
    # Calculate unique card ID (rank * suit combination)
    my $card_id = ($rank_value - 1) * 4 + ($suit_value - 1);  # Offset rank and suit by 1
    
    # Check if the card has already been dealt
    if ($dealt_cards[$card_id]) {
	my $card_str = $card->to_string();
        die "Error: Duplicate card detected $card_str. Program will stop.\n";
    } else {
        # Mark the card as dealt
        $dealt_cards[$card_id] = 1;
    }
}

# ================ Main Logic ===============
# Print Title
print "*** P O K E R  H A N D  A N A L Y Z E R ***\n\n\n";
# Create an array to store the hands
my @hands;

# Initialize six empty hands
for my $i (1 .. 6) {
    my $hand = Hand->new();
    push @hands, $hand;
}

my $num_args = scalar @ARGV;
if ($num_args > 0) {
    print "*** USING TEST DECK ***\n\n";
    my $filename = $ARGV[0] or die "Need to get file name on the  command line\n";
    print "*** File: " . $filename . "\n";
    # Use the filename
    open(DATA, "<$filename") or die "Couldn't open file $filename, $!";

    #the next line puts all the lines from the text file into an array called @all_lines
    my @all_lines = <DATA>;
    my $current_hand = 0;

    foreach my $line (@all_lines) {
        my @tokens = split(',', $line);
        chomp(@tokens);  # Remove newline characters from tokens

        # Trim spaces from each token
        foreach my $token (@tokens) {
            $token =~ s/^\s+|\s+$//g;  # Remove leading and trailing spaces
	    my $rank = substr($token, 0, -1);
	    my $suit = substr($token, -1);

	    my $card = Card->new($rank, $suit);
	    check_for_duplicates($card);
	    $hands[$current_hand]->add_card($card);
	    if ($hands[$current_hand]->card_count() == 5) {
	        $current_hand++;	
            }
        }
		
        # Debug print to check the trimmed tokens
        #print "Tokens: ", join('|', @tokens), "\n";

    }    
    close(DATA);

    # Print each hand
    print "*** Here are the six hands...\n";
    for my $i (0 .. $#hands) {
        print $hands[$i]->to_string() . "\n";
    }

} else {
    print "*** USING RANDOMIZED DECK OF CARDS ***\n\n";
    my $deck = Deck->new();
    $deck->shuffle();
    print "*** Shuffled 52 card deck:\n";
    $deck->print_deck();  
    # Deal five cards to each hand
    for my $card_number (1 .. 5) {
        for my $hand (@hands) {
            my $card = $deck->deal_card();
            $hand->add_card($card);
        }
    }
    
    # Print each hand
    print "*** Here are the six hands...\n";
    for my $i (0 .. $#hands) {
        print $hands[$i]->to_string() . "\n";
    }

    print "\n*** Here is what remains in the deck...\n";
    $deck->print_deck();
}


for my $hand (@hands) {
    HandIdentifier->assign_type($hand);
}

HandSorter::sort_hands(\@hands);

print "\n--- WINNING HAND ORDER ---\n";

for my $i (0 .. $#hands) {
    print $hands[$i]->to_string() . "- " . $hands[$i]->type_to_string() . "\n";
}

