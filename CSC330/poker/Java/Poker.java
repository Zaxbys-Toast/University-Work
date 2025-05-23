import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Poker {
    public static List<Player> readHandsFromFile(String filename) {
        List<Player> players = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                Player player = new Player();
                String[] cards = line.split(",");
                for (String cardStr : cards) {
                    player.dealCard(new Card(cardStr.trim()));
                }
                players.add(player);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }

        return players;
    }

    public static void main(String[] args) {
        List<Player> players;

        if (args.length == 1) {
	    System.out.println("*** Using Test Deck  ***");
	    System.out.println("File - " + args[0]);
            players = readHandsFromFile(args[0]);
        } else {
	    System.out.println("*** Using Random Deck ***");
            Deck deck = new Deck();
            deck.shuffle();
	    deck.printDeck();
            players = new ArrayList<>();

            for (int i = 0; i < 6; i++) {
                Player player = new Player();
                for (int j = 0; j < 5; j++) {
                    player.dealCard(deck.deal());
                }
                players.add(player);
            }
        }
	for (int i = 0; i < 6; i++) {
		players.get(i).printHand();
		System.out.println();
	}
        for (Player player : players) {
            player.sortByRank();
        }

        players.sort(Comparator.comparingInt(Player::handRank).reversed());
	System.out.println("Winning Hands by Type");
        for (int i = 0; i < players.size(); i++) {
            String handType = new String();

            if(players.get(i).handRank() == 1) {
		handType = "High Card";
	    }
            else if(players.get(i).handRank() == 2) {
	    	handType = "One Pair";
	    }
            else if(players.get(i).handRank() == 3) {
                handType = "Two Pair";
            }
	    else if(players.get(i).handRank() == 4) {
                handType = "Three of a Kind";
            }
	    else if(players.get(i).handRank() == 5) {
                handType = "Straight";
            }
	    else if(players.get(i).handRank() == 6) {
                handType = "Flush";
            }
	    else if(players.get(i).handRank() == 7) {
                handType = "Full House";
            }
	    else if(players.get(i).handRank() == 8) {
                handType = "Four of a Kind";
            }
	    else if(players.get(i).handRank() == 9) {
                handType = "Straight Flush";
            }
	    else if(players.get(i).handRank() == 10) {
                handType = "Royal Flush";
            }
            players.get(i).printHand();
	    System.out.print("- " + handType + "\n");
	}
    }
}

