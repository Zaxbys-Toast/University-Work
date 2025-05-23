package Deck;

use strict;
use warnings;
use List::Util qw(shuffle);
use Card;

# Constructor
sub new {
    my ($class) = @_;
    my @suits = ('S', 'H', 'C', 'D');
    my @ranks = ('A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K');
    my @deck;

    # Create a deck of cards
    for my $rank (@ranks) {
        for my $suit (@suits) {
            push @deck, Card->new($rank, $suit);
        }
    }

    # Shuffle the deck
    @deck = shuffle(@deck);

    return bless { cards => \@deck }, $class;
}

# Deal a card (removes and returns the top card)
sub deal {
    my ($self) = @_;
    return pop @{ $self->{cards} };
}

# Print the entire deck
sub print_deck {
    my ($self) = @_;
    my $i = 0;
    for my $card (reverse @{ $self->{cards} }) {
        print "$card   ";
        $i++;
        print "\n" if $i % 13 == 0; # Newline after every 13 cards
    }
    print "\n";
}

# Alias for deal
sub deal_card {
    my ($self) = @_;
    return $self->deal();
}

1;
