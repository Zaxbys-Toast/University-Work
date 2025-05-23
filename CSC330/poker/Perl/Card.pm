package Card;

use strict;
use warnings;

# Maps for ranks and suits
my @RANK_MAP = ('2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A');
my @SUIT_MAP = ('D', 'C', 'H', 'S');

# Constructor
sub new {
    my ($class, $rank, $suit) = @_;
    
    my $rank_index = _get_rank_index($rank);
    my $suit_index = _get_suit_index($suit);

    return bless { rank => $rank_index, suit => $suit_index }, $class;
}

# Private methods for rank and suit index lookup
sub _get_rank_index {
    my ($rank) = @_;
    for my $i (0 .. $#RANK_MAP) {
        return $i + 1 if $RANK_MAP[$i] eq $rank; # 1-based index
    }
    die "Invalid card rank: $rank";
}

sub _get_suit_index {
    my ($suit) = @_;
    for my $i (0 .. $#SUIT_MAP) {
        return $i + 1 if $SUIT_MAP[$i] eq $suit; # 1-based index
    }
    die "Invalid card suit: $suit";
}

# Accessor methods
sub get_rank {
    my ($self) = @_;
    return $self->{rank};
}

sub get_suit {
    my ($self) = @_;
    return $self->{suit};
}

# Method to get the card's string representation
sub to_string {
    my ($self) = @_;
    return $RANK_MAP[$self->{rank} - 1] . $SUIT_MAP[$self->{suit} - 1];
}

# Comparison operators (overload requires the "overload" pragma)
use overload
    '<'  => sub { $_[0]->{rank} < $_[1]->{rank} },
    '==' => sub { $_[0]->{rank} == $_[1]->{rank} && $_[0]->{suit} == $_[1]->{suit} },
    '""' => sub { $_[0]->to_string };

1;
