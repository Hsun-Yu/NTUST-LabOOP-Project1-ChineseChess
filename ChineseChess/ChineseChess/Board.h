#include <vector>
#include <fstream>
#include <iostream>
#include "Chess.h"
#include "Position.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 9

using namespace std;

#pragma once
class Board
{
public:
	Board();
	bool readBoardFile(string filename);
	vector<vector<Chess>> board;

	vector<Chess> & operator [](int index);
	
	vector<Position> goAndEatShare(Position chessPosition);
	vector<Position> whereCanGo(Position chessPosition);	//use position to get ChessTypeID and return every where possible
	vector<Position> whereCanEat(Position chessPosition);	//use position to get ChessTypeID and return every where possible
	Board move(Position lastPosition, Position newPosition);

	bool check(bool whoPlay);
	bool canNotGo(bool whoPlay);

	vector<Position> getAllRedPosition();
	vector<Position> getAllBlackPosition();
};

