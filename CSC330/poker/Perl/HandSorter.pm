package HandSorter;

use warnings;

sub sort_hands {
    my ($hands_ref) = @_;  # Expect a reference to @hands
    sort_hands_by_type($hands_ref);
    sort_ties($hands_ref);  # Sort ties if necessary
}

sub sort_hands_by_type {
    my ($hands_ref) = @_;  # Reference to the array of Hand objects
    # Sort hands in place by handType in descending order
    @$hands_ref = sort { $b->get_type() <=> $a->get_type() } @$hands_ref;
}

sub sort_ties {
    my ($hands_ref) = @_;
    my $start_index = 0;                  # Track the start of a tie group
    @$hands_ref = sort {
        if (!defined $a || !defined $b) {
            die "Undefined hand in array during sort";
        }
        if (!defined $a->get_type() || !defined $b->get_type()) {
            die "Hand type not set in one of the hands during sort";
        }
        $b->get_type() <=> $a->get_type();
    } @$hands_ref;
    my $last_type   = $hands_ref->[0]->get_type();  # Initialize the first handType

    for my $i (0 .. @$hands_ref - 1) {
        my $hand = $hands_ref->[$i];
        if ($hand->get_type() != $last_type) {
            # Sort the tied group
            splice @$hands_ref, $start_index, $i - $start_index,
              @{ sort_subarray([@$hands_ref[$start_index .. $i - 1]]) };

            # Update start index and type
            $start_index = $i;
            $last_type   = $hand->get_type();
        }
        elsif ($i == @$hands_ref - 1) {
            # Sort the final tied group
            splice @$hands_ref, $start_index, $i - $start_index + 1,
              @{ sort_subarray([@$hands_ref[$start_index .. $i]]) };
        }
    }
}
sub sort_subarray {
    my ($hands) = @_;
    my $hand_type = $hands->[0]->get_type();

    if    ($hand_type == 9) { @$hands = sort { compare_royal_flush($b, $a) } @$hands; }
    elsif ($hand_type == 8) { @$hands = sort { compare_straight_flush($b, $a) } @$hands; }
    elsif ($hand_type == 7) { @$hands = sort { compare_four_of_a_kind($b, $a) } @$hands; }
    elsif ($hand_type == 6) { @$hands = sort { compare_full_house($b, $a) } @$hands; }
    elsif ($hand_type == 5) { @$hands = sort { compare_flush($b, $a) } @$hands; }
    elsif ($hand_type == 4) { @$hands = sort { compare_straight($b, $a) } @$hands; }
    elsif ($hand_type == 3) { @$hands = sort { compare_three_of_a_kind($b, $a) } @$hands; }
    elsif ($hand_type == 2) { @$hands = sort { compare_two_pair($b, $a) } @$hands; }
    elsif ($hand_type == 1) { @$hands = sort { compare_pair($b, $a) } @$hands; }
    else                    { @$hands = sort { compare_high_card($b, $a) } @$hands; }

    return $hands;
}

sub compare_royal_flush {
    my ($h1, $h2) = @_;
    my $suit1 = $h1->get_sorted_cards()->[0]->get_suit();
    my $suit2 = $h2->get_sorted_cards()->[0]->get_suit();

    return $suit1 <=> $suit2;
}

sub compare_straight_flush {
    my ($h1, $h2) = @_;
    return compare_straight($h1, $h2);
}

sub compare_four_of_a_kind {
    my ($h1, $h2) = @_;
    return compare_n_of_a_kind($h1, $h2, 4);
}

sub compare_full_house {
    my ($h1, $h2) = @_;
    my $three1 = get_cards_occuring_n_times($h1->get_sorted_cards(), 3)->[0];
    my $three2 = get_cards_occuring_n_times($h2->get_sorted_cards(), 3)->[0];
    return $three1->get_rank() <=> $three2->get_rank()
        || compare_highest_card(
            [grep { $_->get_rank() != $three1->get_rank() } @{ $h1->get_sorted_cards() }],
            [grep { $_->get_rank() != $three2->get_rank() } @{ $h2->get_sorted_cards() }]
        );
}

sub compare_flush {
    my ($h1, $h2) = @_;
    return compare_high_card($h1, $h2);
}

sub compare_straight {
    my ($h1, $h2) = @_;
    my $l1 = $h1->get_sorted_cards();
    my $l2 = $h2->get_sorted_cards();
    return compare_highest_card($l1, $l2);
}

sub compare_three_of_a_kind {
    my ($h1, $h2) = @_;
    return compare_n_of_a_kind($h1, $h2, 3);
}

sub compare_two_pair {
    my ($h1, $h2) = @_;
    return compare_pair($h1, $h2);
}

sub compare_pair {
    my ($h1, $h2) = @_;
    return compare_n_of_a_kind($h1, $h2, 2);
}

sub compare_high_card {
    my ($h1, $h2) = @_;
    my $l1 = $h1->get_sorted_cards();
    my $l2 = $h2->get_sorted_cards();
    return compare_highest_card($l1, $l2);
}

sub compare_highest_card {
    my ($l1, $l2) = @_;
    for my $i (0 .. @$l1 - 1) {
        my $v1 = $l1->[$i]->get_rank();
        my $v2 = $l2->[$i]->get_rank();
        return $v1 <=> $v2 if $v1 != $v2;
    }
    return 0;
}

sub compare_n_of_a_kind {
    my ($h1, $h2, $n) = @_;
    my $c1 = get_cards_occuring_n_times($h1->get_sorted_cards(), $n)->[0];
    my $c2 = get_cards_occuring_n_times($h2->get_sorted_cards(), $n)->[0];
    return $c1->get_rank() <=> $c2->get_rank();
}

sub get_cards_occuring_n_times {
    my ($cards, $n) = @_;
    my %count;
    $count{$_->get_rank()}++ for @$cards;
    return [grep { $count{$_->get_rank()} == $n } @$cards];
}

1;
