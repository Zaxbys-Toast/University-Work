import java.util.*;
import java.io.*;
public class Bingo
{	
  private static BitSet chosenNum = new BitSet(76);
  public static int[][] bingoCard = new int[5][5];
//Main method. calls fillCard to add values to the array bingoCard, prints the starting state of the card using printCard
//and then runs playGame to do the rest.
  public static void main(String[] args){
    fillCard(bingoCard); 
    printCard();
    playGame();  
  }
//Fills an array using the bingo.in file
  public static void fillCard(int[][] arr) 
  {
        try{
        Scanner stdin = new Scanner(new File("bingo.in"));
        for (int i = 0; i < 5; i++) {
          for (int j = 0; j < 5; j++) {
            arr[i][j] = stdin.nextInt();
          }
        }
  
        }
        catch(FileNotFoundException ex){
          System.out.println("File Not Found");
        }    
  }
//Formats and prints all of the values in the array into a bingo card
  public static void printCard()
  {
    System.out.print("YOUR BINGO CARD: \n\nB     I     N     G     O\n---------------------------\n");
    for (int i = 0; i < 5; i++)  
    { 
      for(int j = 0; j < 5; j++)
      {
	 if(bingoCard[i][j] == 0)
	 {
	    System.out.print("| X   "); //Replaces and chosen values with an X
         }	
	 else if(bingoCard[i][j] < 10)  
         {
	  System.out.print("| " + bingoCard[i][j] + "   ");  //Keeps single digit numbers in line with the double digit numbers
	 } 
         else
         {
          System.out.print("|" + bingoCard[i][j] + "   ");
         }
      }	
      System.out.print("\n---------------------------\n\n");
    }    
  }

//Mainly calls upon the other methods to piece everything together
  public static void  playGame()  
  {   
//This allows for a record of how many numbers are tried
   int count = 0;
//Allows for the type of win to be determined
   int winType = 0;
   System.out.println("BINGO NUMBERS PICKED AT RANDOM FROM BIN: ");
//Generates a random number and marks it. Prints the number and checks for a win.  
   do 
   {
     numGen();
     winType = checkForWin();
     count++;
     if(count % 9 == 0)
     {
       System.out.println(" ");
     }
   }
   while(winType < 1); 
//Chooses the correct win message based on winType
   switch(winType) 
   {
     case 1:
       System.out.println("\nYOU WIN WITH A HORIZONTAL BINGO AFTER " + count + " PICKS!");
       break;
     case 2: 
       System.out.println("\nYOU WIN WITH A VERTICAL BINGO AFTER " + count + " PICKS!");
       break;
     case 3:
       System.out.println("\nYOU WIN WITH A DIAGONAL BINGO AFTER " + count + " PICKS!");
       break;
   }
   printCard(); 
  } 
//Generates random numbers between 1 and 75. Determines if they are duplicates and marks off non-duplicates.  
  public static void numGen()
  {
    int currNum = Math.round((int)(Math.random() * 74 + 1)) ; //Generates a random integer between 1 and 75
    while (chosenNum.get(currNum) == true)  //If the number has already been chosen a new number will be generated
    {
      currNum = Math.round((int)(Math.random() * 74 + 1));
    }
    chosenNum.set(currNum);
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        if (bingoCard[i][j] == currNum)
        {
          bingoCard[i][j] = 0;
        }
      }
    }
//Prints the number that was chosen to show the user what numbers were chosen.
    if(currNum < 10)
    {
      System.out.print(" ");
    }
    System.out.print("  " + currNum);    
  }

//Determines if the game has been "won" by using the sum methods.    
  public static int checkForWin()  
  { 
//Used to determine if there is a diagonal win
    int diagonalSumLeft = 0;
    int diagonalSumRight = 0; 
    int winType = 0; //no win 
    for (int i = 0; i < 5; i++)
    {
      int sum = sumHorizontal(i);
      if(sum == 0)
      {
       winType = 1;
       break;    
      }
    }
    for (int j = 0; j < 5; j++)
    {
     int sum = sumVertical(j);
      if(sum == 0)
      {
        winType = 2;
        break;
      }
    }
//Sums up the diagonals to determine if there is a win or not
    for(int i = 0; i < 5; i++)
    {
      diagonalSumLeft += bingoCard[i][i];    
    }
    for(int i = 0; i < 5; i++)
    {
      diagonalSumRight += bingoCard[i][4-i];
    }
    if(diagonalSumLeft == 0 || diagonalSumRight == 0)
    {
      winType = 3;
    }
//Returns an int that will tell the playGame method what case to consider
   return winType;
 }   
//Sums up each of the values in row i    
  public static int sumHorizontal(int i) 
  {
    int sum = 0;
    for(int j = 0; j < 5; j++)
    {
      sum += bingoCard[i][j];
    }
//Returns the value of the sum (if it is 0 that means there is a win)    
    return sum;  
  }
//Sums up each of the values in column j     
  public static int sumVertical(int j)  
  {  
    int sum = 0; 
    for(int i = 0; i < 5; i++) 
    {
     sum += bingoCard[i][j];
    }
//returns the sum of those values
    return sum;
  }  
 

  
    
}

    
