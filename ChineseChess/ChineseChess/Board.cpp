#include "Board.h"
#include "Position.h"

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

/*
intent: operator overload []
pre:	int ----index
post:	vector<Chess>	----from Game::Board
*/
vector<Chess>& Board::operator[](int index)
{
	return Board::board[index];
}

/*
intent: get list of all position of where can go
pre:	Position	----chess position
post:	vector<Position>	----list of all position of where can go
*/
vector<Position> Board::whereCanGo(Position chessPosition)
{
	//TODO (HsunYu):unfinished
	int chessTypeID = Board::board[chessPosition.y][chessPosition.x].typeID;
	vector<Position> result;

	//Show all possible
	switch ((chessTypeID % 7))
	{
	default:
		break;
	case 1://將,帥
		if (chessTypeID == 1)	//將
		{
			//x must in [3, 5]
			//y must in [0, 2]
			for (int i = 0; i <= 2; i++)
			{
				for (int j = 3; j <= 5; j++)
				{
					if ((chessPosition.y == i && abs(chessPosition.x - j) == 1) ||
						(chessPosition.x == j && abs(chessPosition.y - i) == 1))
					{
						result.push_back(Position(j, i));
					}
				}
			}
		}
		else if (chessTypeID == 8)	//帥
		{
			//x must in [3, 5]
			//y must in [7, 9]
			for (int i = 7; i <= 9; i++)
			{
				for (int j = 3; j <= 5; j++)
				{
					if ((chessPosition.y == i && abs(chessPosition.x - j) == 1) ||
						(chessPosition.x == j && abs(chessPosition.y - i) == 1))
					{
						result.push_back(Position(j, i));
					}
				}
			}
		}
		break;
	case 2://士,仕
		break;
	case 3://象,相
		break;
	case 4://車,車
		break;
	case 5://馬,傌
		break;
	case 6://包,炮
		break;
	case 0://卒,兵
		break;
	}

	//Delete position if the position has already had chess
	return result;
}

/*
intent: get list of all position of where can eat
pre:	Position	----chess position
post:	vector<Position>	----list of all position of where can eat
*/
vector<Position> Board::whereCanEat(Position chessPosition)
{
	//TODO (HsunYu)
	int chessTypeID = Board::board[chessPosition.y][chessPosition.x].typeID;

	return vector<Position>();
}

