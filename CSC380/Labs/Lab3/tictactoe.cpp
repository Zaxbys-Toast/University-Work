#include <iostream>
#include <string>
using namespace std;

enum Player {
	Human = -1,
	Blank = 0,
	Computer = 1
};

/*
 *
 *    In your playGame method, you will set up a loop like this :
 *    while (true)
 *    {
 *    		Human makes move & check for winner
 *    		Machine makes best move & check for winner
 *    		Exit when winner found
 *    }
 *
 *    When human selects, remember to input-- to be in range on your array.
 *
 *    HINT when human moves:
 *                    Player human = Human;
 *                    board[input] = human;
 *    HINT when computer moves:
 *                    Player computer = Computer;
 *                    board[input] = computer;
 *

 *
 * */

void printBoard(Player board[]);
void playGame(Player board[]);
bool checkWin(Player board[]);
bool checkFull(Player board[]);
int sumCol(Player board[], int colNum);
int sumRow(Player board[], int rowNum);
int sumDia(Player board[], int diaNum);
int decision(Player board[], int lastDec, int dec);

int main() {
	char play = 'Y';

	while(play == 'Y' || play == 'y') {
		Player board[9] = {Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank,Blank};
		printBoard(board);
		playGame(board);
		cout << "Do you want to play again? (Y/N) ";
		cin >> play;
		cout << endl;
	}
	return 0;
}

void printBoard(Player board[]) {
	
	for(int i = 0; i < 9; i++) {
		if((i == 2) || (i == 5) || (i == 8)) {
			if(board[i] == -1)
				cout << " X";
			else if (board[i] == 1)
				cout << " O";
			else
				cout << "  ";
		} else {
			if(board[i] == -1)
                                cout << "  X |";
                        else if (board[i] == 1)
                                cout << "  O |";
                        else
                                cout << "    |";
		}
		if(((i+1)%3 == 0) && (i != 8)) {
			cout << endl << "----|----|----" << endl;
		}
		if(i == 8)
			cout << endl;
	}

}

void playGame(Player board[])
{
	Player computer = Computer;
	Player human = Human;
	int choice;
	bool over = false;
	while(over == false)
	{
		int dec = 10;
		int choice = -1;
		//Human turn
		cout << "Choose which square you would like to play in" << endl;
		cin >> choice;
		while (choice < 1 &&  choice > 9)
		{
			cout << "Invalid choice. Pick a square 1 through 9" << endl;
			cin >> choice;
		}
		while (board[choice] == -1 || board[choice] == 1)
		{
			cout << "You cannot go there. Choose another square." << endl;
			cin >> choice;
		}
		board[choice - 1] = human;
		printBoard(board);
		over = checkWin(board);
		over = checkFull(board);
		 cout << "\033[2J\033[1;1H";
		//AI turn
		int maxChoice = -1;		
		board[decision(board, choice, dec)] = computer;
		printBoard(board);
		over = checkWin(board);
		over = checkFull(board);
		
	}


}

bool checkWin(Player board[])
{
	/*
	//My original idea was this. I decided I could better do this using several functions that sum the rows cols and 
	//diagonals which can be reused with determining where to put the next mark
	if ( board[0] + board[1] + board[2] == 3 || board[0] + board[1] + board[2] == -3)
	{
		return true;
	}
	if ( board[3] + board[4] + board[5] == 3 || board[3] + board[4] + board[5] == -3)
        {
		return true;
        }
	if ( board[6] + board[7] + board[8] == 3 || board[6] + board[7] + board[8] == -3)
        {
		return true;
        }
 	if ( board[0] + board[4] + board[8] == 3 || board[0] + board[4] + board[8] == -3) 
        {
		return true;
        }

 	if ( board[2] + board[4] + board[6] == 3 || board[2] + board[4] + board[6] == -3)
        {
		return true;
        }
 	if ( board[0] + board[3] + board[6] == 3 || board[0] + board[3] + board[6] == -3)
        {
		return true;
        }
 	if ( board[2] + board[5] + board[8] == 3 || board[2] + board[5] + board[8] == -3)
        {
		return true;
        }
 	if ( board[1] + board[4] + board[7] == 3 || board[1] + board[4] + board[7] == -3)
        {
		return true;
        }
	else
		return false;
	*/	
	for (int i = 0; i < 3; i++)
	{
		if(sumCol(board, i) == 3 || sumCol(board, i) == -3)
			return true;
		if(sumRow(board, i) == 3 || sumRow(board, i) == -3)
			return true;
	}
	if(sumDia(board, 0) == 3 || sumDia(board, 0) == -3)
		return true;
	if(sumDia(board, 1) == 3 || sumDia(board, 1) == -3)
		return true;
		
}

bool checkFull(Player board[])
{
	for(int i = 0; i < 9; i++)
	{
		if(board[i] == 0)
			return false;
	}
	return true;
}

int sumCol(Player board[], int colNum)
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum += board[colNum + (i * 3)];
	}
	return sum;
}

int sumRow(Player board[], int rowNum)
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum += board[rowNum + i];
	}
	return sum;
}

int sumDia(Player board[], int diaNum)
{
	int sum = 0;
	if (diaNum = 1)
	{
		sum += board[0] + board[4] + board[8];
	}
	else
		sum += board[2] + board[4] + board[6];
	return sum;
}

int decision(Player board[], int lastDec, int dec)
{
	Player temp[9];
	for(int i = 0; i < 9; i++)
	{
		temp[i] = board[i];
	}
	if(checkWin(board))
	{
		return dec;
	}
	for (int i = 0; i < 3; i++)
	{
		//winning
		if(sumCol(board, i) == 2)
		{
			if(board[i] == 0)
			{
				dec = i;
				return dec;
			}
			else if(board[i+3] == 0)
			{
				dec = i + 3;
				return dec;
			}
			else
			{
				dec = i + 6;
				return dec;
			}
		}
		else if(sumRow(board, i) == 2)
		{
			if(board[i] == 0)
			{
				dec = i;
				return dec;
			}
			else if(board[i+1] == 0)
			{
				dec = i + 1;
				return dec;
			}
			else
			{
				dec = i + 2;
				return dec;
			}
		}
		//Blocking oponents win
		else if(sumCol(board, i) == -2)
		{
			if(board[i] == 0)
			{
				dec = i;
				return dec;
			}
			else if(board[i+3] == 0)
			{
				dec = i + 3;
				return dec;
			}
			else
			{
				dec = i + 6;
				return dec;
			}
		}
		else if(sumRow(board, i) == -2)
		{
			if(board[i] == 0)
			{
				dec = i;
				return dec;
			}
			else if(board[i+1] == 0)
			{
				dec = i + 1;
				return dec;
			}
			else
			{
				dec = i + 2;
				return dec;
			}
		}
		//making two lines of two
//Couldn't think of a good solution right now
//		else if(sumRow(board, 0))
//		{
//
//		}
		//play center
		else if(board[4] == 0)
		{
			dec = 4;
			return dec;
		}

		//If oponent played in corner play opposite corner
		else if(lastDec == 0 || lastDec == 2 || lastDec == 6 || lastDec == 8)
		{
			if(lastDec == 0)
				if(board[8] == 0)
				{
					dec = 8;
				}
			else if(lastDec == 2)
				if(board[6] == 0)
				{
					dec = 6;
				}	
			else if(lastDec == 6)
				if(board[2] == 0)
				{
					dec = 2;
				}
			else if (board[0] == 0)
				dec = 0;
			return dec; 
		}
		//If empty corner play there
		else if(board[0] == 0 || board[2] == 0 || board[6] == 0 || board[8] == 0)
		{
			if(board[0] == 0)
				dec = 0;
			else if(board[2] == 0)
				dec = 2;
			else if(board[6] == 0)
				dec = 6;
			else if(board[8] == 0)
				dec = 8;
			return dec;
		}
		//Choose first empty square
		else
		{
			if(board[i] == 0)
			{
				dec = i;
				return dec;
			}
		}
	}
}
