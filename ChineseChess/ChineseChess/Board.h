#include <vector>
#include <fstream>
#include <iostream>
#include "Chess.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 9

using namespace std;

#pragma once
class Board
{
public:
	Board();
	bool readBoardFile(string);
	vector<vector<Chess>> board;

	vector<Chess> & operator [](int);
	
	//vector<Position> whereCanGo(Position);	//use position to get ChessTypeID and return every where possible
	//vector<Position> whereCanEat(Position);	//use position to get ChessTypeID and return every where possible
};

