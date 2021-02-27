#include "TicTacToe.h"

#include <iostream>
#include <algorithm>
#include <windows.h>
#include <cstdlib>


TicTacToe::TicTacToe() 
{
	numPlayersActive = 0;
	std::fill(boardState, boardState + 9, 0);
}

/**
 * Adds a player to the game.
 *
 * The game is created with two players by default.
 * This method formally registers each of them 
 * and specifies if they should be played by an AI or not.
 *
 * @param isAI : boolean specifying if it should be played by an AI or not.
 */
void TicTacToe::AddPlayer(bool isAI)
{
	if (numPlayersActive == 0)
	{
		p1.isAI = isAI;
		numPlayersActive++;
	}
	else {
		p2.isAI = isAI;
		numPlayersActive++;
	}
}

/**
 * Applies a move to the board.
 *
 * @param move : integer move to be applied
 * @param player : player number of the player making the move
 * @return boolean, if the move was successfully made.
 */
bool TicTacToe::MakeMove(int move, int player)
{

	/*
		1	2	3
	   -----------
	1 | 0   1   2
	2 | 3   4   5
	3 | 6   7   8

	Say input is 12 (col 1, row 2). The token would be placed at 3.
	*/

	int x = floor(move / 10);
	int y = (move - (x * 10));

	int ind = (y - 1) * 3;
	
	switch (x)
	{
	// case a changes nothing
	case 2:
		ind += 1;
		break;
	case 3:
		ind += 2;
		break;
	}

	if (boardState[ind] > 0 || !(move == 11 || move == 12 || move == 13 || move == 21 || move == 22 || move == 23 || move == 31 || move == 32 || move == 33))
		return false;

	boardState[ind] = player; 

	PrintBoard();
	return true;
}

/**
 * Translates and prints the storing array into a visual
 * grid representation of TicTacToe.
 *
 */
void TicTacToe::PrintBoard()
{
	char toPrint[9];
	std::cout << "\n\n";

	for (int i = 0; i < 9; i++)
	{
		switch (boardState[i])
		{
		case 0:
			toPrint[i] = ' ';
			break;

		case 1:
			toPrint[i] = 'X';
			break;

		case 2:
			toPrint[i] = 'O';
			break;
		default:
			toPrint[i] = '_';
		}
	}

	std::cout << "      1  2  3 ";
	std::cout << "\n     ---------";

	std::cout << "\n  1 | " << toPrint[0] << "  " << toPrint[1] << "  " << toPrint[2];
	std::cout << "\n  2 | " << toPrint[3] << "  " << toPrint[4] << "  " << toPrint[5];
	std::cout << "\n  3 | " << toPrint[6] << "  " << toPrint[7] << "  " << toPrint[8] << "\n\n";
}

/**
 * Checks if the game has ended.
 *
 * @return integer representing the winner's player number. -1 if the game has not ended.
 */
int TicTacToe::GameHasEnded()
{
	// look for any line of three
	/*
		1 	2	3 			1	2	3 			1	2	3 			1	2	3 			1	2	3 		    1   2   3 			1	2	3 			1	2	3
	   -----------	 	   ----------- 		   ----------- 		   ----------- 		   ----------- 		   ----------- 		   ----------- 		   ----------- 
	1 |[0]  1   2	 	1 | 0  [1]   2		1 | 0   1  [2]		1 |[0   1   2]	 	1 | 0   1   2  		1 | 0   1   2  		1 |[0]  1   2		1 | 0   1  [2]
	2 |[3]  4   5		2 | 3  [4]   5		2 | 3   4  [5]		2 | 3   4   5		2 |[3   4   5]		2 | 3   4   5		2 | 3  [4]  5		2 | 3  [4]  5 
	3 |[6]  7   8		3 | 6  [7]   8		3 | 6   7  [8]		3 | 6   7   8		3 | 6   7   8		3 |[6   7   8]		3 | 6   7  [8]		3 |[6]  7   8


	*/

	bool col1Win = (boardState[0] > 0) && (boardState[0] == boardState[3]) && (boardState[0] == boardState[6]);
	bool col2Win = (boardState[1] > 0) && (boardState[1] == boardState[4]) && (boardState[1] == boardState[7]);
	bool col3Win = (boardState[2] > 0) && (boardState[2] == boardState[5]) && (boardState[2] == boardState[8]);

	bool row1Win = (boardState[0] > 0) && (boardState[0] == boardState[1]) && (boardState[0] == boardState[2]);
	bool row2Win = (boardState[3] > 0) && (boardState[3] == boardState[4]) && (boardState[3] == boardState[5]);
	bool row3Win = (boardState[6] > 0) && (boardState[6] == boardState[7]) && (boardState[6] == boardState[8]);

	bool diagTopDownWin = (boardState[0] > 0) && (boardState[0] == boardState[4]) && (boardState[0] == boardState[8]);
	bool diagBotUpWin = (boardState[6] > 0) && (boardState[6] == boardState[4]) && (boardState[6] == boardState[2]);


	if (col1Win || row1Win || diagTopDownWin)
		return boardState[0];

	if (col2Win || row2Win || diagBotUpWin)
		return boardState[4];

	if (row3Win || col3Win)
		return boardState[8];

	bool space = false;
	for (int i = 0; i < 9; i++)
	{
		if (boardState[i] == 0) {
			space = true;
			break;
		}
	}
	if (space == false)
		return 0;

	return -1;
}

/**
 * Clears the console application.
 * 
 * Source: Joma @  https://stackoverflow.com/questions/6486289/how-can-i-clear-console
 */
void TicTacToe::Clear()
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}

/**
 * Starts and runs the game of TicTacToe.
 */
void TicTacToe::StartGame()
{
	
	int move = 00;

	std::cout << p1.isAI << " and " << p2.isAI;

	while (true)
	{

		// Player 1
		Clear();
		std::cout << "The game has started!" << "\n\n" << "Please type in the coordinates of your move when it is your turn (Column then row).";
		std::cout << "\n" << "E.g. \"12\" to place your mark in the first column, second row.";

		PrintBoard();
		std::cout << "\nPlayer 1's Turn! \nPlease enter your move: ";
		std::cin >> move; 
		bool responsep1 = MakeMove(move, 1);
		while (!(responsep1)) {
			Clear();
			std::cout << "The game has started!" << "\n\n" << "Please type in the coordinates of your move when it is your turn (Column then row).";
			std::cout << "\n" << "E.g. \"12\" to place your mark in the first column, second row.";

			PrintBoard();
			std::cout << "\nPlayer 1's Turn! \nThat wasn't a valid move. Please enter your (valid) move: ";
			std::cin >> move;
			responsep1 = MakeMove(move, 1);
		}
		
		
		std::cout << responsep1;

		int winner = GameHasEnded();
		if (winner != -1)
		{
			Clear();
			std::cout << "The game has ended";
			PrintBoard();
			if (winner == 0)
				std::cout << "It's a tie.";
			else
				std::cout << "Player 1 is the winner!";
			break;
		}
		
		Clear();
		std::cout << "The game has started!" << "\n\n" << "Please type in the coordinates of your move when it is your turn (Column then row).";
		std::cout << "\n" << "E.g. \"12\" to place your mark in the first column, second row.";
		
		// Player 2

		if (p2.isAI)
		{
			PrintBoard();
			std::cout << "The Computer is choosing a move...";
			Sleep(1000);
			move = p2.GetNextMove(boardState);
			bool responseAI = MakeMove(move, 2);
			PrintBoard();

		}
		else {
			PrintBoard();
			std::cout << "Player 2's Turn!" << "\n" << "Please enter your move: ";
			std::cin >> move; 
			bool responsep2 = MakeMove(move, 2);
			while (!(responsep2)) {
				Clear();
				std::cout << "The game has started!" << "\n\n" << "Please type in the coordinates of your move when it is your turn (Column then row).";
				std::cout << "\n" << "E.g. \"12\" to place your mark in the first column, second row.";

				PrintBoard();
				std::cout << "\n" << "Player 2's Turn!" << "\n" << "That wasn't a valid move. Please enter your (valid) move: ";
				std::cin >> move;
				responsep2 = MakeMove(move, 2);
			}
			
			std::cout << responsep2;

			int winner = GameHasEnded();
			if (winner != -1)
			{
				Clear();
				std::cout << "The game has ended.";
				PrintBoard();
				if (winner == 0)
					std::cout << "It's a tie.";
				else
					std::cout << "Player 2 is the winner!";
				break;
			}
		}
		
	}
	
	std::cout << "\n\n -- Game Finished --";
	getchar();
}