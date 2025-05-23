using System;
using System.Collections.Generic;
using System.Linq;

public class Player
{
    private List<Card> hand;

    public Player()
    {
        hand = new List<Card>();
    }

    public List<Card> GetHand()
    {
        return hand;
    }

    public void DealCard(Card card)
    {
        if (hand.Count < 5)
        {
            hand.Add(card);
        }
    }

    public void SortByRank()
    {
        hand = hand.OrderByDescending(c => c.GetRankValue()).ToList();
    }

    public void SortBySuit()
    {
        hand = hand.OrderByDescending(c => c.GetSuitValue()).ToList();
    }

    public bool IsRoyal()
    {
        return IsFlush() && IsStraight() && hand[^1].GetRank() == 'T';
    }

    public bool IsStraightFlush()
    {
        return IsFlush() && IsStraight();
    }

    public bool IsFour()
    {
        return (hand[0].GetRank() == hand[1].GetRank() &&
                hand[1].GetRank() == hand[2].GetRank() &&
                hand[2].GetRank() == hand[3].GetRank()) ||
               (hand[1].GetRank() == hand[2].GetRank() &&
                hand[2].GetRank() == hand[3].GetRank() &&
                hand[3].GetRank() == hand[4].GetRank());
    }

    public bool IsFull()
    {
        return (hand[0].GetRank() == hand[1].GetRank() &&
                hand[1].GetRank() == hand[2].GetRank() &&
                hand[3].GetRank() == hand[4].GetRank()) ||
               (hand[2].GetRank() == hand[3].GetRank() &&
                hand[3].GetRank() == hand[4].GetRank() &&
                hand[0].GetRank() == hand[1].GetRank());
    }

    public bool IsFlush()
    {
        return hand.All(c => c.GetSuit() == hand[0].GetSuit());
    }

    public bool IsStraight()
    {
        for (int i = 0; i < 4; i++)
        {
            if (hand[i].GetRankValue() - 1 != hand[i + 1].GetRankValue())
            {
                return false;
            }
        }
        return true;
    }

    public bool IsThree()
    {
        return (hand[0].GetRank() == hand[1].GetRank() && hand[1].GetRank() == hand[2].GetRank()) ||
               (hand[1].GetRank() == hand[2].GetRank() && hand[2].GetRank() == hand[3].GetRank()) ||
               (hand[2].GetRank() == hand[3].GetRank() && hand[3].GetRank() == hand[4].GetRank());
    }

    public bool IsTwo()
    {
        return (hand[0].GetRank() == hand[1].GetRank() && hand[2].GetRank() == hand[3].GetRank()) ||
               (hand[1].GetRank() == hand[2].GetRank() && hand[3].GetRank() == hand[4].GetRank());
    }

    public bool IsPair()
    {
        return hand[0].GetRank() == hand[1].GetRank() ||
               hand[1].GetRank() == hand[2].GetRank() ||
               hand[2].GetRank() == hand[3].GetRank() ||
               hand[3].GetRank() == hand[4].GetRank();
    }

    public int HandRank()
    {
        if (IsRoyal()) return 10;
        if (IsStraightFlush()) return 9;
        if (IsFour()) return 8;
        if (IsFull()) return 7;
        if (IsFlush()) return 6;
        if (IsStraight()) return 5;
        if (IsThree()) return 4;
        if (IsTwo()) return 3;
        if (IsPair()) return 2;
        return 1;
    }

    public void PrintHand()
    {
        foreach (Card card in hand)
        {
            Console.Write(card.ToString() + " ");
        }
        
    }
}

