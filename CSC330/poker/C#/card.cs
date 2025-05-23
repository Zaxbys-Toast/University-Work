using System;

public class Card
{
    private char rank;
    private char suit;

    public Card(char rank, char suit)
    {
        this.rank = rank;
        this.suit = suit;
    }

    public Card(string cardStr)
    {
        if (cardStr.Length == 3 && cardStr.Substring(0, 2) == "10")
        {
            rank = 'T';
            suit = cardStr[2];
        }
        else if (cardStr.Length == 2)
        {
            rank = cardStr[0];
            suit = cardStr[1];
        }
        else
        {
            throw new ArgumentException("Invalid card string format");
        }
    }

    public char GetRank()
    {
        return rank;
    }

    public char GetSuit()
    {
        return suit;
    }

    public int GetRankValue()
    {
        string order = "23456789TJQKA";
        return order.IndexOf(rank);
    }

    public int GetSuitValue()
    {
        string order = "DCHS";
        return order.IndexOf(suit);
    }

    public override string ToString()
    {
        return $"{rank}{suit}";
    }
}

