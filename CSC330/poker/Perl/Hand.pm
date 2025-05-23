package Hand;

use strict;
use warnings;
use Card;

# Constants
use constant {
    HAND_SIZE => 5,
    HAND_MAP  => [
        "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
        "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Straight Flush"
    ],
};

# Constructor
sub new {
    my ($class) = @_;
    return bless {
        cards    => [],  # Empty array of cards
        handType => -1,  # Default invalid hand type
    }, $class;
}

# String method to represent the hand as a string
sub to_string {
    my ($self) = @_;
    my $result = join(" ", map { $_->to_string() } @{ $self->{cards} }) . " ";
    return $result;
}

# Add a card to the hand
sub add_card {
    my ($self, $card) = @_;
    push @{ $self->{cards} }, $card;
}

# Get the type of the hand
sub get_type {
    my ($self) = @_;
    return $self->{handType};
}

# Set the type of the hand
sub set_type {
    my ($self, $type) = @_;
    $self->{handType} = $type;
}

# Get sorted cards based on rank
sub get_sorted_cards {
    my ($self) = @_;
    my @sorted_cards = sort { $b->get_rank() <=> $a->get_rank() } @{ $self->{cards} };
    return \@sorted_cards;
}

sub card_count {
    my ($self) = @_;
    return scalar @{ $self->{cards} }; # Return the number of cards in the hand
}
sub type_to_string {
    my ($self) = @_;
    return HAND_MAP->[$self->{handType}];
}
1;
