# Deck Class - Python

from card import Card
import random

class Deck:
    
    def __init__(self):
        self.cardDeck = []
        
        suits = ['h', 'c', 's', 'd']
        ranks = ['2','3','4','5','6','7','8','9','10','J','Q','K','A']
        for suit in suits:
            for rank in ranks:
                self.cardDeck.append(Card(suit, rank))
    

    def shuffle(self):
        random.shuffle(self.cardDeck)
    
    def dealCard(self):
        return self.cardDeck.pop()
    
    def printDeck(self):
        print("Deck\n----")
        for card in self.cardDeck:
            print(f"{card.rank}{card.suit.upper()}",end="  ")
        
        print("\n----")
    
    def __str__(self):
        return ", ".join([f"{card.rank}{card.suit.upper()}" for card in self.cardDeck])
