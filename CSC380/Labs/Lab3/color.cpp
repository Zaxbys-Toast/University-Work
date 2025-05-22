void printBoard(Player board[]) {

	//The "\e[34m" just colors the text
	//34 colors the X's blue
	//31 colors the O's red
	//0 resets the colors back to normal
	for(int i = 0; i < 9; i++) {
		if((i == 2) || (i == 5) || (i == 8)) {
			if(board[i] == -1)
				cout << "\e[34m X\e[0m";
			else if (board[i] == 1)
				cout << "\e[31m O\e[0m";
			else
				cout << "  ";
		} else {
			if(board[i] == -1)
				cout << "\e[34m  X \e[0m|";
			else if (board[i] == 1)
				cout << "\e[31m  O \e[0m|";
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
