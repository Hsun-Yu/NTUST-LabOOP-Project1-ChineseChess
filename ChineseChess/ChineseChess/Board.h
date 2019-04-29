#include <vector>
#include "Chess.h"

using namespace std;

#pragma once
class Board
{
public:
	Board();
	bool readBoardFile(string);
	vector<vector<Chess>> board;
};

