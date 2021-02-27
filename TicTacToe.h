
#include "Player.h"
#include <string>

class TicTacToe
{

public:
	TicTacToe();
	void AddPlayer(bool isAI);
	void StartGame();
	void Clear();

private:
	int boardState[9];
	int numPlayersActive;
	Player p1; // X
	Player p2; // O

	bool MakeMove(int move, int player);
	void PrintBoard();
	int GameHasEnded();

};

