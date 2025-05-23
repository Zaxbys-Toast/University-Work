package main


func (h *Hand) AssignType() {
	cards := h.GetSortedCards()

	if is_royal(cards) {
		h.SetType(9)
	}else if is_straight_flush(cards) {
                h.SetType(8)
        }else if is_four(cards) {
                h.SetType(7)
        }else if is_full(cards) {
                h.SetType(6)
        }else if is_flush(cards) {
                h.SetType(5)
        }else if is_straight(cards) {
                h.SetType(4)
        }else if is_three(cards) {
                h.SetType(3)
        }else if is_two_pair(cards) {
                h.SetType(2)
        }else if is_pair(cards) {
                h.SetType(1)
        }else {
		h.SetType(0)
	}


}

func getFrequencyRank(hand []Card) map[int]int {
    rankCounts := make(map[int]int)

    for _, card := range hand {
        rankCounts[card.rank]++
    }

    return rankCounts
}

func is_royal(cards []Card) bool {
	if is_flush(cards) && is_straight(cards) {
		if(cards[0].rank == 10) {
			return true
		}
	}
	return false
}

func is_straight_flush(cards []Card) bool {
	if is_straight(cards) && is_flush(cards) {
		return true
	}
	return false
}
func is_straight(cards []Card) bool {
	if is_low_straight(cards) {
		return true
	}
	for i := 1; i < len(cards); i++ {
		if cards[i-1].rank-1 != cards[i].rank {
			return false
		}
	}
	return true
}
func is_low_straight(cards []Card) bool {
	if (cards[0].rank == 12 &&
	   cards[1].rank == 3 &&
	   cards[2].rank == 2 &&
	   cards[3].rank == 1 &&
	   cards[4].rank == 0) {
		return true
	}
	return false
}
func is_flush(cards []Card) bool {
	for i := 1; i < len(cards); i++ {
		if cards[i].suit != cards[0].suit {
			return false
		}
	}
	return true
}

func is_four(cards []Card) bool {
	rankCounts := getFrequencyRank(cards)
	for _, count := range rankCounts {
		if count == 4 {
			return true
		}
	}
	return false
}

func is_full(cards []Card) bool {
	rankCounts := getFrequencyRank(cards)
	hasThree := false
	hasTwo := false
	for _, count := range rankCounts {
		if count == 3 {
			hasThree = true
		}
		if count == 2 {
			hasTwo = true
		}
	}
	return hasThree && hasTwo
}

func is_three(cards []Card) bool {
	rankCounts := getFrequencyRank(cards)
	for _, count := range rankCounts {
		if count == 3 {
			return true
		}
	}
	return false
}

func is_two_pair(cards []Card) bool {
	rankCounts := getFrequencyRank(cards)
	pairCount := 0
	for _, count := range rankCounts {
		if count == 2 {
			pairCount++
		}
	}
	return pairCount == 2
}

func is_pair(cards []Card) bool {
	rankCounts := getFrequencyRank(cards)
	for _, count := range rankCounts {
		if count == 2 {
			return true
		}
	}
	return false
}
