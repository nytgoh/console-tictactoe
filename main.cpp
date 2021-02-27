#include <iostream>
#include "TicTacToe.h"


/**
 * Runs the TicTacToe Application.
 *
 * This console application game can be played as local 2-player
 * or single player against a computer AI.
 *
 */
int main()
{
	int playMode;

	TicTacToe game;
	game.AddPlayer(false); // p1

	std::cout << "Welcome to TicTacToe! \n\nType [1] to play against the computer. Type [2] to play local 2-player.\n";
	std::cin >> playMode;

	while (playMode != 1 && playMode != 2)
	{
		game.Clear();
		std::cout << "Please enter a valid option! \n\nType [1] to play against the computer. Type [2] to play local 2-player.\n";
		std::cin >> playMode;
	}

	// p2
	if (playMode == 1)
	{
		game.AddPlayer(true);
	}
	else if (playMode == 2)
	{
		game.AddPlayer(false);
	}

	game.StartGame();

}