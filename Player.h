#pragma once
#include <algorithm>
#include <iterator>
#include <tuple>
class Player
{

public:

	Player();
	bool isAI;

	int GetNextMove(int* boardState);
	
private:
	// AI stuff
	std::tuple<int, int> Minimax(int* board, int depth, bool isAIturn);
	int GetMoveFromInd(int ind);
	int GameFinished(int* boardState);

};

