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
	Board::board.clear();
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
intent: some type of chesses use the same way to eat or go so this can help to share code
pre:	Position	----chess position
post:	vector<Position>	----list of all position of where can go
*/
vector<Position> Board::goAndEatShare(Position chessPosition)
{
	if (Board::board[chessPosition.y][chessPosition.x].typeID == 0)
		return vector<Position>();

	int chessTypeID = Board::board[chessPosition.y][chessPosition.x].typeID;
	vector<Position> result;

	//Show all possible
	switch ((chessTypeID % 7))
	{
	default:
		break;
	case 1://將,帥
		if (chessTypeID <= 7)	//將
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
		else //帥
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
		if (chessTypeID <= 7)	//士
		{
			//x must in [3, 5]
			//y must in [0, 2]
			for (int i = chessPosition.y - 1; i <= chessPosition.y + 1; i += 2)
			{
				for (int j = chessPosition.x - 1; j <= chessPosition.x + 1; j += 2)
				{
					if (j >= 3 && j <= 5 && i >= 0 && i <= 2)
						result.push_back(Position(j, i));
				}
			}
		}
		else	//仕
		{
			//x must in [3, 5]
			//y must in [7, 9]
			for (int i = chessPosition.y - 1; i <= chessPosition.y + 1; i += 2)
			{
				for (int j = chessPosition.x - 1; j <= chessPosition.x + 1; j += 2)
				{
					if (j >= 3 && j <= 5 && i >= 7 && i <= 9)
						result.push_back(Position(j, i));
				}
			}
		}
		break;
	case 3://象,相
		if (chessTypeID <= 7)	//象
		{
			//x must in [0, 8]
			//y must in [0, 4]
			for (int i = -1; i <= 1; i += 2)
			{
				for (int j = -1; j <= 1; j += 2)
				{
					int newI = 2 * i + chessPosition.y;
					int newJ = 2 * j + chessPosition.x;
					if (newI >= 0 && newI <= 4 &&
						newJ >= 0 && newJ <= 8)
					{
						if (Board::board[chessPosition.y + i][chessPosition.x + j].typeID == 0)
							result.push_back(Position(newJ, newI));
					}
				}
			}
		}
		else	//相
		{
			//x must in [0, 8]
			//y must in [0, 4]
			for (int i = -1; i <= 1; i += 2)
			{
				for (int j = -1; j <= 1; j += 2)
				{
					int newI = 2 * i + chessPosition.y;
					int newJ = 2 * j + chessPosition.x;
					if (newI >= 5 && newI <= 9 &&
						newJ >= 0 && newJ <= 8)
					{
						if (Board::board[chessPosition.y + i][chessPosition.x + j].typeID == 0)
							result.push_back(Position(newJ, newI));
					}
				}
			}
		}
		break;
	case 4://車,車
	case 6://包,炮
		//x must in [0, 8]
		//y must in [0, 9]

		//Search right
		for (int i = chessPosition.x + 1; i <= 8; i++)
		{
			result.push_back(Position(i, chessPosition.y));
			if (Board::board[chessPosition.y][i].typeID != 0)
				break;
		}

		//Search left
		for (int i = chessPosition.x - 1; i >= 0; i--)
		{
			result.push_back(Position(i, chessPosition.y));
			if (Board::board[chessPosition.y][i].typeID != 0)
				break;
		}

		//Search up
		for (int i = chessPosition.y - 1; i >= 0; i--)
		{
			result.push_back(Position(chessPosition.x, i));
			if (Board::board[i][chessPosition.x].typeID != 0)
				break;
		}

		//Search down
		for (int i = chessPosition.y + 1; i <= 9; i++)
		{
			result.push_back(Position(chessPosition.x, i));
			if (Board::board[i][chessPosition.x].typeID != 0)
				break;
		}
		break;
	case 5://馬,傌
		//x must in [0, 8]
		//y must in [0, 9]

		//Check right
		if (chessPosition.x + 2 <= 8)
		{
			if (Board::board[chessPosition.y][chessPosition.x + 1].typeID == 0)
			{
				if (chessPosition.y - 1 >= 0)
					result.push_back(Position(chessPosition.x + 2, chessPosition.y - 1));
				if (chessPosition.y + 1 <= 9)
					result.push_back(Position(chessPosition.x + 2, chessPosition.y + 1));
			}
		}

		//Check left
		if (chessPosition.x - 2 >= 0)
		{
			if (Board::board[chessPosition.y][chessPosition.x - 1].typeID == 0)
			{
				if (chessPosition.y - 1 >= 0)
					result.push_back(Position(chessPosition.x - 2, chessPosition.y - 1));
				if (chessPosition.y + 1 <= 9)
					result.push_back(Position(chessPosition.x - 2, chessPosition.y + 1));
			}
		}

		//Check up
		if (chessPosition.y - 2 >= 0)
		{
			if (Board::board[chessPosition.y - 1][chessPosition.x].typeID == 0)
			{
				if (chessPosition.x - 1 >= 0)
					result.push_back(Position(chessPosition.x - 1, chessPosition.y - 2));
				if (chessPosition.x + 1 <= 8)
					result.push_back(Position(chessPosition.x + 1, chessPosition.y - 2));
			}
		}

		//Check down
		if (chessPosition.y + 2 <= 9)
		{
			if (Board::board[chessPosition.y + 1][chessPosition.x].typeID == 0)
			{
				if (chessPosition.x - 1 >= 0)
					result.push_back(Position(chessPosition.x - 1, chessPosition.y + 2));
				if (chessPosition.x + 1 <= 8)
					result.push_back(Position(chessPosition.x + 1, chessPosition.y + 2));
			}
		}
		break;
	case 0://卒,兵
		if (chessTypeID <= 7)	//卒
		{
			if (chessPosition.y <= 4)
				result.push_back(Position(chessPosition.x, chessPosition.y + 1));
			else
			{
				if (chessPosition.y + 1 <= 9)
					result.push_back(Position(chessPosition.x, chessPosition.y + 1));
				if (chessPosition.x - 1 >= 0)
					result.push_back(Position(chessPosition.x - 1, chessPosition.y));
				if (chessPosition.x + 1 <= 8)
					result.push_back(Position(chessPosition.x + 1, chessPosition.y));
			}

		}
		else	//兵
		{
			if (chessPosition.y >= 5)
				result.push_back(Position(chessPosition.x, chessPosition.y - 1));
			else
			{
				if (chessPosition.y - 1 >= 0)
					result.push_back(Position(chessPosition.x, chessPosition.y - 1));
				if (chessPosition.x - 1 >= 0)
					result.push_back(Position(chessPosition.x - 1, chessPosition.y));
				if (chessPosition.x + 1 <= 8)
					result.push_back(Position(chessPosition.x + 1, chessPosition.y));
			}
		}
		break;
	}

	return result;
}

/*
intent: get list of all position of where can go
pre:	Position	----chess position
post:	vector<Position>	----list of all position of where can go
*/
vector<Position> Board::whereCanGo(Position chessPosition)
{
	vector<Position> result = Board::goAndEatShare(chessPosition);

	int chessTypeID = Board::board[chessPosition.y][chessPosition.x].typeID;
	//Delete position if the position has already had chess
	for (int i = 0; i < result.size(); i++)
	{
		if (Board::board[result[i].y][result[i].x].typeID != 0)
		{
			result.erase(result.begin() + i);
			i--;
		}
	}

	return result;
}

/*
intent: get list of all position of where can eat
pre:	Position	----chess position
post:	vector<Position>	----list of all position of where can eat
*/
vector<Position> Board::whereCanEat(Position chessPosition)
{
	vector<Position> result;
	int chessTypeID = Board::board[chessPosition.y][chessPosition.x].typeID;

	if (chessTypeID % 7 == 6)	//炮,包
	{
		//Up
		for (int i = chessPosition.y - 1; i >= 1; i--)
		{
			if (Board::board[i][chessPosition.x].typeID != 0)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					if (Board::board[j][chessPosition.x].typeID != 0)
					{
						result.push_back(Position(chessPosition.x, j));
						i = -1;
						break;
					}
				}
			}
		}

		//Down
		for (int i = chessPosition.y + 1; i <= 8; i++)
		{
			if (Board::board[i][chessPosition.x].typeID != 0)
			{
				for (int j = i + 1; j <= 9; j++)
				{
					if (Board::board[j][chessPosition.x].typeID != 0)
					{
						result.push_back(Position(chessPosition.x, j));
						i = 10;
						break;
					}
				}
			}
		}

		//Left
		for (int i = chessPosition.x - 1; i >= 1; i--)
		{
			if (Board::board[chessPosition.y][i].typeID != 0)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					if (Board::board[chessPosition.y][j].typeID != 0)
					{
						result.push_back(Position(j, chessPosition.y));
						i = -1;
						break;
					}
				}
			}
		}

		//Right
		for (int i = chessPosition.x + 1; i <= 7; i++)
		{
			if (Board::board[chessPosition.y][i].typeID != 0)
			{
				for (int j = i + 1; j <= 8; j++)
				{
					if (Board::board[chessPosition.y][j].typeID != 0)
					{
						result.push_back(Position(j, chessPosition.y));
						i = 9;
						break;
					}
				}
			}
		}
	}
	else if (chessTypeID % 7 == 1)	//將,帥
	{
		result = goAndEatShare(chessPosition);

		if (chessTypeID <= 7)	//將
		{
			for (int i = chessPosition.y + 1; i <= 9; i++)
			{
				if (Board::board[i][chessPosition.x].typeID == 8)	//if is 帥
					result.push_back(Position(chessPosition.x, i));
				else if (Board::board[i][chessPosition.x].typeID == 0)
					continue;
				else
					break;
			}
		}
		else	//帥
		{
			for (int i = chessPosition.y - 1; i >= 0; i--)
			{
				if (Board::board[i][chessPosition.x].typeID == 1)	//if is 將
					result.push_back(Position(chessPosition.x, i));
				else if (Board::board[i][chessPosition.x].typeID == 0)
					continue;
				else
					break;
			}
		}
	}
	else
		result = goAndEatShare(chessPosition);

	//Delete position of space and my chesses
	for (int i = 0; i < result.size(); i++)
	{
		if (!(chessTypeID <= 7 && Board::board[result[i].y][result[i].x].typeID >= 8) &&
			!(chessTypeID >= 8 &&
			Board::board[result[i].y][result[i].x].typeID <= 7 &&
			Board::board[result[i].y][result[i].x].typeID >= 1))
		{
			result.erase(result.begin() + i);
			i--;
		}
	}

	return result;
}

/*
intent: move chess
pre:	
	Position: last position
	Position: new position
post:	Board	----new board
*/
Board Board::move(Position lastPosition, Position newPosition)
{
	Board b = (*this);
	b[newPosition.y][newPosition.x] = Board::board[lastPosition.y][lastPosition.x];
	b[lastPosition.y][lastPosition.x] = Chess(0);

	return b;
}

/*
intent: tell player Check!! yuor chess
pre:	bool	----whoPlay red: true black: false
post:	bool	----need to check: true
*/
bool Board::check(bool whoPlay)
{
	vector<Position> checkEat;
	if (!whoPlay)	//black
		checkEat = Board::getAllRedPosition();
	else	//red
		checkEat = Board::getAllBlackPosition();

	for (int i = 0; i < checkEat.size(); i++)
	{
		vector<Position> p = Board::whereCanEat(checkEat[i]);

		for (int j = 0; j < p.size(); j++)
		{
			if ((Board::board[p[j].y][p[j].x].typeID) % 7 == 1)
				return true;
		}
	}

	return false;
}

/*
intent: if you go you will be lose
pre:	bool	----whoPlay
post:	bool	---- if you can go: false	if you cannot go: true
*/
vector<Position> Board::canNotGoFilter(bool whoPlay, Position chessPosition, vector<Position> possible)
{
	Position bossPosition;

	//get boss position
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if ((Board::board[i][j].typeID == 1 && !whoPlay) || 
				(Board::board[i][j].typeID == 8 && whoPlay))
			{
				bossPosition = Position(j, i);
				i = BOARD_HEIGHT;
				break;
			}
		}
	}

	for (int i = 0; i < possible.size(); i++)
	{
		Board possibleBoard = Board::move(chessPosition, possible[i]);
		vector<Position> enemyChess;

		//get enemy chess
		if (whoPlay)	//red
			enemyChess = possibleBoard.getAllBlackPosition();
		else	//black
			enemyChess = possibleBoard.getAllRedPosition();

		if (possibleBoard.check(whoPlay))
			possible.erase(possible.begin() + i--);
	}

	return possible;
}

/*
intent: get all red chesses position
pre:	null
post:	vector<Position>	----List of position of red chesses
*/
vector<Position> Board::getAllRedPosition()
{
	vector<Position> res;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (Board::board[i][j].typeID > 7)
			{
				res.push_back(Position(j, i));
			}
		}
	}
	return res;
}

/*
intent: get all black chesses position
pre:	null
post:	vector<Position>	----List of position of black chesses
*/
vector<Position> Board::getAllBlackPosition()
{
	vector<Position> res;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (Board::board[i][j].typeID < 8 && Board::board[i][j].typeID > 0)
			{
				res.push_back(Position(j, i));
			}
		}
	}
	return res;
}

