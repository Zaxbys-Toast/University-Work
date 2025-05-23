package HandIdentifier;

use strict;
use warnings;
use List::Util qw(all);

# Assign the type to the given hand
sub assign_type {
    my ($class, $hand) = @_;
    my $cards = $hand->get_sorted_cards();

    if ($class->is_royal_straight_flush($cards)) {
        $hand->set_type(9);
    } elsif ($class->is_straight_flush($cards)) {
        $hand->set_type(8);
    } elsif ($class->is_four_of_a_kind($cards)) {
        $hand->set_type(7);
    } elsif ($class->is_full_house($cards)) {
        $hand->set_type(6);
    } elsif ($class->is_flush($cards)) {
        $hand->set_type(5);
    } elsif ($class->is_straight($cards)) {
        $hand->set_type(4);
    } elsif ($class->is_three_of_a_kind($cards)) {
        $hand->set_type(3);
    } elsif ($class->is_two_pair($cards)) {
        $hand->set_type(2);
    } elsif ($class->is_pair($cards)) {
        $hand->set_type(1);
    } else {
        $hand->set_type(0); # High Card
    }
}

# Check if cards form a Royal Straight Flush
sub is_royal_straight_flush {
    my ($class, $cards) = @_;
    return $class->is_royal_straight($cards) && $class->is_flush($cards);
}

# Check if cards form a Royal Straight
sub is_royal_straight {
    my ($class, $cards) = @_;
    return defined($cards->[0]->{rank}) && $cards->[0]->{rank} == 13 &&
           defined($cards->[1]->{rank}) && $cards->[1]->{rank} == 12 &&
           defined($cards->[2]->{rank}) && $cards->[2]->{rank} == 11 &&
           defined($cards->[3]->{rank}) && $cards->[3]->{rank} == 10 &&
           defined($cards->[4]->{rank}) && $cards->[4]->{rank} == 9;
}
sub is_low_straight {
    my ($class, $cards) = @_;
    return defined($cards->[0]->{rank}) && $cards->[0]->{rank} == 13 &&
           defined($cards->[1]->{rank}) && $cards->[1]->{rank} == 4 &&
           defined($cards->[2]->{rank}) && $cards->[2]->{rank} == 3 &&
           defined($cards->[3]->{rank}) && $cards->[3]->{rank} == 2 &&
           defined($cards->[4]->{rank}) && $cards->[4]->{rank} == 1;

}
# Check if cards form a Straight Flush
sub is_straight_flush {
    my ($class, $cards) = @_;
    return $class->is_straight($cards) && $class->is_flush($cards);
}

# Check if cards form a Flush
sub is_flush {
    my ($class, $cards) = @_;
    my $prev_suit = $cards->[0]->{suit};
    return all { defined($_->{suit}) && $_->{suit} eq $prev_suit } @$cards;
}

# Check if cards form a Straight
sub is_straight {
    my ($class, $cards) = @_;
    return 1 if $class->is_royal_straight($cards);
    return 1 if $class->is_low_straight($cards);

    my $prev_value = $cards->[0]->{rank};
    
    for my $i (1 .. $#{$cards}) {
        my $curr_value = $cards->[$i]->{rank};	
        return 0 if !defined($curr_value) || $curr_value != $prev_value - 1;
        $prev_value = $curr_value;
    }
    return 1;
}

# Get frequency of each rank in the cards
sub get_frequency_rank {
    my ($class, $cards) = @_;
    my %rank_counts;

    foreach my $card (@$cards) {
        my $rank = $card->{rank};
        if (defined($rank)) {
            $rank_counts{$rank}++;
        }
    }
    return \%rank_counts;
}

# Check if cards form Four of a Kind
sub is_four_of_a_kind {
    my ($class, $cards) = @_;
    my $rank_counts = $class->get_frequency_rank($cards);
    return defined($rank_counts) && join(',', sort { $a <=> $b } values %$rank_counts) eq '1,4';
}

# Check if cards form a Full House
sub is_full_house {
    my ($class, $cards) = @_;
    my $rank_counts = $class->get_frequency_rank($cards);
    return defined($rank_counts) && join(',', sort { $a <=> $b } values %$rank_counts) eq '2,3';
}

# Check if cards form Three of a Kind
sub is_three_of_a_kind {
    my ($class, $cards) = @_;
    my $rank_counts = $class->get_frequency_rank($cards);
    return defined($rank_counts) && join(',', sort { $a <=> $b } values %$rank_counts) eq '1,1,3';
}

# Check if cards form Two Pair
sub is_two_pair {
    my ($class, $cards) = @_;
    my $rank_counts = $class->get_frequency_rank($cards);
    return defined($rank_counts) && join(',', sort { $a <=> $b } values %$rank_counts) eq '1,2,2';
}

# Check if cards form a Pair
sub is_pair {
    my ($class, $cards) = @_;
    my $rank_counts = $class->get_frequency_rank($cards);
    return defined($rank_counts) && join(',', sort { $a <=> $b } values %$rank_counts) eq '1,1,1,2';
}

1;
