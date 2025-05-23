# Card Class - Python

class Card:
    
    # Card constructor

    def __init__(self, suit, rank): 
        suit = suit.lower()
        validSuit = ['h', 's', 'c', 'd', 'H', 'S', 'C', 'D']
        
        if suit in validSuit:
            self.suit = suit
        else:
            raise ValueError("Not a recognized card suit. Enter either h, s, d, or c.")
        
        validRank = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        if rank in validRank:
            self.rank = rank
        else:
            raise ValueError("Not a valid card")
    
    def printCard(self):
        # Print the Rank. If the card is a face card print out the first letter       
        print(f"{self.rank}",end="")

        # Print the suit of the card in upper case
        print(f"{(self.suit).upper()}",end="  ")
    
