using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Program
{
    static List<Player> ReadHandsFromFile(string filename)
    {
        List<Player> players = new List<Player>();

        try
        {
            using (StreamReader file = new StreamReader(filename))
            {
                string line;
                while ((line = file.ReadLine()) != null)
                {
                    Player player = new Player();
                    string[] cardStrs = line.Split(',');
                    foreach (string cardStr in cardStrs)
                    {
                        string trimmedCardStr = cardStr.Trim();
                        Card card = new Card(trimmedCardStr);
                        player.DealCard(card);
                    }
                    players.Add(player);
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error opening file: {filename}\n{ex.Message}");
            Environment.Exit(1);
        }

        return players;
    }

bool comparePlayers(Player p1, Player p2)
{
    if (p1.HandRank() == p2.HandRank())
    {
        var hand1 = p1.GetHand();
        var hand2 = p2.GetHand();

        for (int i = 0; i < hand1.Count; i++)
        {
            if (hand1[i].GetRankValue() != hand2[i].GetRankValue())
            {
                return hand1[i].GetRankValue() > hand2[i].GetRankValue();
            }
            // If ranks are equal, compare suits in Spades, Hearts, Clubs, Diamonds order
            if (hand1[i].GetSuitValue() != hand2[i].GetSuitValue())
            {
                return hand1[i].GetSuitValue() < hand2[i].GetSuitValue();
            }
        }
        return false; // If all cards are equal
    }
    return p1.HandRank() > p2.HandRank();
}

    static void Main(string[] args)
    {
        List<Player> players;

        if (args.Length == 1)
        {
            players = ReadHandsFromFile(args[0]);
        }
        else
        {
	    Console.WriteLine("*** Random Deck ***");
            Deck deck = new Deck();
            deck.Shuffle();
	    deck.PrintDeck();
	    Console.WriteLine();
            players = new List<Player>();

            for (int i = 0; i < 6; i++)
            {
                Player player = new Player();
                for (int j = 0; j < 5; j++)
                {
                    player.DealCard(deck.Deal());
                }
                players.Add(player);
            }
        }

        foreach (Player player in players)
        {
            player.SortByRank();
        }
	Console.WriteLine("Player Hands");
	for ( int i = 0; i < players.Count; i++) {
		players[i].PrintHand();
		Console.WriteLine();
	}
// Sort players by hand rank, then by card ranks, then by suits
 	players = players.OrderByDescending(p => p.HandRank())
                  .ThenByDescending(p => p.GetHand().Select(c => c.GetRankValue()).FirstOrDefault())
                  .ThenByDescending(p => p.GetHand().Select(c => c.GetSuitValue()).FirstOrDefault())
                  .ToList();
	Console.WriteLine("Player Hands by Rank");
        for (int i = 0; i < players.Count; i++)
        {
            players[i].PrintHand();
            Console.Write("- ");
            switch (players[i].HandRank())
            {
                case 1: Console.Write("High Card"); break;
                case 2: Console.Write("One Pair"); break;
                case 3: Console.Write("Two Pair"); break;
                case 4: Console.Write("Three of a Kind"); break;
                case 5: Console.Write("Straight"); break;
                case 6: Console.Write("Flush"); break;
                case 7: Console.Write("Full House"); break;
                case 8: Console.Write("Four of a Kind"); break;
                case 9: Console.Write("Straight Flush"); break;
            }
            Console.WriteLine();
        }
    }
}

// Comparer class for sorting cards by rank and suit
class CardComparer : IComparer<Card>
{
    public int Compare(Card x, Card y)
    {
        int rankComparison = y.GetRankValue().CompareTo(x.GetRankValue());
        if (rankComparison == 0)
        {
            return x.GetSuitValue().CompareTo(y.GetSuitValue());
        }
        return rankComparison;
    }
}

