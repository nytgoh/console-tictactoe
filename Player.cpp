#include "Player.h"
#include "TicTacToe.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <tuple>

Player::Player(){}

/**
 * Gets the AI's next move.
 * 
 * Calls minimax and extracts the move from the result.
 *
 * @param : takes in a board state (int array)
 * @return integer representing the winner's player number. -1 if the game has not ended.
 */
int Player::GetNextMove(int* boardState)
{
	int toUse[9];
	for (int i = 0; i < 9; i++)
	{
		toUse[i] = *(boardState + i);
	}
	std::tuple<int, int> result = Minimax(toUse, 0, true);
	return std::get<0>(result);
}

/**
 * Checks if the game has ended.
 *
 * @param boardState : takes in a board state (int array)
 * @return integer representing the winner's player number. -1 if the game has not ended.
 */
int Player::GameFinished(int* boardState)
{
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
 * Translate a 0-9 index position into a move.
 *
 * @param ind : integer index to translate
 * @return the "Move" representation of an index position in the array
 */
int Player::GetMoveFromInd(int ind)
{
	switch (ind)
	{
	case 0:
		return 11;

	case 1:
		return 21;

	case 2:
		return 31;

	case 3:
		return 12;

	case 4:
		return 22;

	case 5:
		return 32;

	case 6:
		return 13;

	case 7:
		return 23;

	case 8:
		return 33;
	}
}

/**
 * Uses the Minimax decision rule (with recursion) to find the AI's next move.
 *
 * @param board : current state of the game to build off
 * @param depth : how many steps into the future the current state is
 * @param isAIturn : specifies whose turn it is
 * @return tuple<int, int> : holds the move and the value of the state created after the move
 */
std::tuple<int, int> Player::Minimax(int* board, int depth, bool isAIturn)
{

	int winner = GameFinished(board);
	
	if (winner != -1)
	{
		if (winner == 1) // player
			return std::make_tuple(0, 15 - depth); 
		else if (winner == 2) // opponent
			return std::make_tuple(0, -15 + depth);
		else
			return std::make_tuple(0, 0); // tie
	}
	else 
	{

		int smallestValue = 100;
		int smallestMove = 11;

		int largestValue = -100;
		int largestMove = 11;

		for (int j = 0; j < 9; j++)
		{

			if ((board[j]) == 0) 
			{

				int nextState[9];
				for (int i = 0; i < 9; i++)
				{
					nextState[i] = *(board + i);
				}
				nextState[j] = isAIturn ? 2 : 1; 

				std::tuple<int, int> response = Minimax(nextState, depth + 1, isAIturn ? false : true); 

				int value = std::get<1>(response); 

				if (value < smallestValue)
				{
					smallestValue = value;
					smallestMove = GetMoveFromInd(j);
				}
				if (value > largestValue)
				{
					largestValue = value;
					largestMove = GetMoveFromInd(j);
				}


			}

		}

		if (isAIturn) // AI is player 2 (opponent) and will choose the smallest value
		{
			return std::make_tuple(smallestMove, smallestValue);
		}
		else 
		{
			return std::make_tuple(largestMove, largestValue);
		}

		}
}
