#include "Board.h"

using namespace std;
#define BOARD_HEIGHT 10
#define BOARD_WIDTH 9

Board::Board()
{

}

/*
intent: To read file and put chesses into the board
pre: 
	string -----filename
post: 
	bool ------whoPlay
*/
bool Board::readBoardFile(string filename)
{
	ifstream file(filename);
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		vector<Chess> v;
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			int id;
			file >> id;
			v.push_back(Chess(id));
		}

		Board::board.push_back(v);
	}

	bool whoPlay;
	file >> whoPlay;
	return whoPlay;
}

vector<Chess>& Board::operator[](int index)
{
	return Board::board[index];
}

