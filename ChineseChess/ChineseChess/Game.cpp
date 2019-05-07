#include "Game.h"

using namespace std;

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;

Game::Game()
{
	Game::initialize();
	Game::display();
	Game::inGame();
}

Game::~Game()
{
}

/*
Intent:To initialize the game
Pre:null
Post:null
*/
void Game::initialize()
{
	system("chcp 65001");

	cout << "1. New Game" << endl;
	cout << "2. Last Game" << endl;
	cout << "Input number:" << endl;
	while (1)
	{
		if (!getInitialType())
			cout << "Please input the correct number!!" << endl;
		else
			break;
	}
	
	//int x = getchar();

	if (Game::whoPlay)
	{
		//red

		for (int i = 7; i < BOARD_HEIGHT; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (Game::board[i][j].typeID == 8)
				{
					Game::chessMarkPosition = Position(j, i);
				}
			}
		}
	}
	else
	{
		//black
		for (int i = 0; i < 3; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (Game::board[i][j].typeID == 1)
				{
					Game::chessMarkPosition = Position(j, i);
				}
			}
		}
	}
}

/*
Intent: user will input a initial type number from console
Pre:null
Post:
	bool ----if user input correct number return true, if not return false
*/
bool Game::getInitialType()
{
	int number;
	
	cin >> number;

	//TODO: For test !!!!!!!
	//number = 1;
	
	switch (number)
	{
	case 1:
		newGame();
		break;
	case 2:
		lastGame();
		break;
	default:
		return false;
		break;
	}
	return true;
}

/*
intent: read initial board
pre: null
post: null
*/
void Game::newGame()
{
	Game::whoPlay = Game::board.readBoardFile("Chessboard/Initial.txt");
}

/*
intent: read file to board
pre: null
post: null
*/
void Game::lastGame()
{
	string filename;
	ifstream file;
	do
	{
		cout << "please input filename:" << endl;
		cin >> filename;
		file = ifstream(filename);
	} while (!file.is_open());
	
	Game::whoPlay = Game::board.readBoardFile(filename);
}

/*
intent: Print a string serveral times.
pre: str, times
post: void
*/
void Game::outputCount(string str, int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << str;
	}
}

void Game::display()
{
	system("cls");
	ifstream inputS("Chessboard\\board_template.txt");
	string str;
	
	while (getline(inputS, str))
	{
		cout << str << endl;
	}

	inputS.close();

	// Board start in (29, 2) (黑車)

	setTextStyle(PURPLE, WHITE);
	setCursorXY(24, 1);
	cout << "１　２　３　４　５　６　７　８　９";

	setTextStyle(BLACK, WHITE);
	setCursorXY(24, 2);
	cout << "－－－－－－－－－－－－－－－－－";
	
	setCursorXY(24, 3);
	cout << "｜　｜　｜　｜＼｜／｜　｜　｜　｜";

	setCursorXY(24, 4);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 5);
	cout << "｜　｜　｜　｜／｜＼｜　｜　｜　｜";

	setCursorXY(24, 6);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 7);
	cout << "｜　｜　｜　｜　｜　｜　｜　｜　｜";

	setCursorXY(24, 8);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 9);
	cout << "｜　｜　｜　｜　｜　｜　｜　｜　｜";

	setCursorXY(24, 10);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 11);
	cout << "｜　　　楚河　　　　　漢界　　　｜";

	setCursorXY(24, 12);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 13);
	cout << "｜　｜　｜　｜　｜　｜　｜　｜　｜";

	setCursorXY(24, 14);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 15);
	cout << "｜　｜　｜　｜　｜　｜　｜　｜　｜";

	setCursorXY(24, 16);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 17);
	cout << "｜　｜　｜　｜＼｜／｜　｜　｜　｜";

	setCursorXY(24, 18);
	cout << "｜－＋－＋－＋－＋－＋－＋－＋－｜";

	setCursorXY(24, 19);
	cout << "｜　｜　｜　｜／｜＼｜　｜　｜　｜";

	setCursorXY(24, 20);
	cout << "－－－－－－－－－－－－－－－－－";

	setTextStyle(PURPLE, WHITE);
	setCursorXY(24, 21);
	cout << "九　八　七　六　五　四　三　二　一";

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (Game::board[i][j].typeID == 0) continue;
			Game::board[i][j].colour ? setTextStyle(RED, GRAY) : setTextStyle(BLACK, GRAY);
			setCursorXY(24 + j * 4, 2 + i * 2);
			cout << Game::board[i][j].show;
		}
	}

	// Move cursor to below
	setTextStyle(WHITE, BLACK);
	setCursorBoardXY(Position(0, 0));
}

/*
intent: Mark the specified position.
pre: position.
post: void.
*/
void Game::markOnScreen(Position pos, int backgroundColor)
{
	int color, typeID = Game::board[pos.y][pos.x].typeID;
	string show;

	show = Game::board[pos.y][pos.x].show;
	
	if(typeID > 7)
	{
		color = RED;
	}
	else
	{
		color = BLACK;
		if (typeID == 0)
		{
			if (pos.y == 0 || pos.y == BOARD_HEIGHT - 1)
			{
				show = "－";
			}
			else if (pos.x == 0 || pos.x == BOARD_WIDTH - 1)
			{
				show = "｜";
			}
			else
			{
				show = "＋";
			}
		}
	}
	
	setTextStyle(color, backgroundColor);
	setCursorBoardXY(pos);
	cout << show;
}

/*
intent: Cancel selecting the chess.
pre:
	pos: position that you want to unmark.
post: void.
*/
void Game::unmarkOnScreen(Position pos)
{
	int backgroundColor, typeID = Game::board[pos.y][pos.x].typeID;

	if (typeID == 0)
	{
		backgroundColor = WHITE;
	}
	else
	{
		backgroundColor = GRAY;
	}

	Game::markOnScreen(pos, backgroundColor);
}

/*
intent: Change text style
pre: 
	int color: BLACK, WHITE, RED, GREEN, BLUEL, CYAN, PURPLE
	int backgroundColor: Same with color.
post: void.
*/
void Game::setTextStyle(int color, int backgroundColor)
{
	SetConsoleTextAttribute(Game::outputHandle, color | (backgroundColor * 16));
}

void Game::setCursorXY(int x, int y)
{
	Game::cursorXY.X = x;
	Game::cursorXY.Y = y;
	SetConsoleCursorPosition(Game::outputHandle, Game::cursorXY);
}

void Game::setCursorBoardXY(Position pos)
{
	Game::setCursorXY(24 + pos.x * 4, 2 + pos.y * 2);
}

void Game::moveCursor(int x, int y)
{
	Game::setCursorXY(Game::cursorXY.X + x, Game::cursorXY.Y + y);
}

/*
intent: save game to file
pre: 
	string ----filename
post: null
*/
void Game::saveGame(string filename)
{
	ofstream file(filename);

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH - 1; j++)
			file << Game::board.board[i][j].typeID << " ";

		file << Game::board.board[i][BOARD_WIDTH - 1].typeID << endl;
	}
	file << Game::whoPlay;
}

void Game::inGame()
{


	int enterCount = 0;

	while (1)
	{
		Game::setCursorBoardXY(Game::chessMarkPosition);
		char c = 0;
		c = _getch();
		if (c == 13) //Enter
		{
			selectChess(enterCount);
		}
		else if (c == 8) //Backspace
		{
			if(enterCount == 1)
			{
				Game::chessMarkPosition = Game::lastPosition;
				enterCount = 0;
			}
			else
				continue;
		}
		else
		{
			vector<Position> allRedPosition;
			allRedPosition = Game::getAllRedPosition();
			vector<Position> allBlackPosition;
			allBlackPosition = Game::getAllBlackPosition();
			vector<Position> objPosition;

			if (whoPlay)
				objPosition = allRedPosition;
			else
				objPosition = allBlackPosition;
			c = _getch();
			switch (c)
			{
			case 72:

				Game::chessMarkPosition = Up(objPosition); //Up
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 80:
				Game::chessMarkPosition = Down(objPosition); //Down
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 75:
				Game::chessMarkPosition = Left(objPosition); //Left
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 77:
				Game::chessMarkPosition = Right(objPosition); //Right
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			default: 
				break;
			}
		}
	}
}

Position Game::Up(vector<Position> objPosition)
{
	Position p = Game::chessMarkPosition;

	if(p.y == 0) //hit ceiling
		return p;
	else
	{
		for (int i = p.y - 1; i >= 0; i--)
		{
			for(int j = 0 ; j < objPosition.size() ; j++)
			{
				if(objPosition[j].x == p.x && objPosition[j].y == i)
				{
					p.y = i;
					return p;
				}
			}
		}
		return p;
		//if((Game::chessMarkPosition.x + 1) >= BOARD_WIDTH)
		//	return Game::chessMarkPosition;
		//else
		//{
		//	for(int i = Game::chessMarkPosition.x + 1 ; i < BOARD_WIDTH ; i++)
		//	{
		//		for(int j = 0 ; j < BOARD_HEIGHT ; j++)
		//		{
		//			for(int k = 0 ; k < objPosition.size() ; k++)
		//			{
		//				if(objPosition[k].x == i && objPosition[k].y == j)
		//				{
		//					Game::chessMarkPosition.x = i;
		//					Game::chessMarkPosition.y = j;
		//					return Game::chessMarkPosition;
		//				}
		//			}
		//		}
		//	}
		//	return Game::chessMarkPosition;	//if nothing can find		
		//}
	}
}

Position Game::Down(vector<Position> objPosition)
{
	Position p = Game::chessMarkPosition;
	if(p.y == BOARD_HEIGHT - 1) //hit floor
		return p;
	else
	{
		for (int i = p.y + 1; i < BOARD_HEIGHT ; i++)
		{
			for(int j = 0 ; j < objPosition.size() ; j++)
			{
				if(objPosition[j].x == p.x && objPosition[j].y == i)
				{
					p.y = i;
					return p;
				}
			}
		}
		return p;
		//if((Game::chessMarkPosition.x + 1) >= BOARD_WIDTH)
		//	return Game::chessMarkPosition;
		//else
		//{
		//	for(int i = Game::chessMarkPosition.x + 1 ; i < BOARD_WIDTH ; i++)
		//	{
		//		for(int j = BOARD_HEIGHT - 1 ; j >= 0 ; j--)
		//		{
		//			for(int k = 0 ; k < objPosition.size() ; k++)
		//			{
		//				if(objPosition[k].x == i && objPosition[k].y == j)
		//				{
		//					Game::chessMarkPosition.x = i;
		//					Game::chessMarkPosition.y = j;
		//					return Game::chessMarkPosition;
		//				}
		//			}
		//		}
		//	}
		//	return Game::chessMarkPosition;	//if nothing can find
		//}
	}
}

Position Game::Left(vector<Position> objPosition)
{
	Position p = Game::chessMarkPosition;

	if(p.x == 0) //hit leftwall
		return p;
	for (int i = p.x - 1; i >= 0; i--)
	{
		vector<Position> v;
		for (int k = 0; k < objPosition.size(); k++)
		{
			if (objPosition[k].x == i)
				v.push_back(objPosition[k]);
		}

		if (v.size() != 0)
		{
			Position smallP = v[0];
			for (int j = 0; j < v.size(); j++)
			{
				if (abs(smallP.y - p.y) > abs(v[j].y - p.y))
					smallP = v[j];
			}
			return smallP;
		}
	}
	return p;	//if nothing can find		

}

Position Game::Right(vector<Position> objPosition)
{
	Position p = Game::chessMarkPosition;

	if(p.x == BOARD_WIDTH - 1) //hit rightwall
		return p;
	for (int i = p.x + 1; i < BOARD_WIDTH; i++)
	{
		vector<Position> v;
		for (int k = 0; k < objPosition.size(); k++)
		{
			if (objPosition[k].x == i)
				v.push_back(objPosition[k]);
		}

		if (v.size() != 0)
		{
			Position smallP = v[0];
			for (int j = 0; j < v.size(); j++)
			{
				if (abs(smallP.y - p.y) > abs(v[j].y - p.y))
					smallP = v[j];
			}
			return smallP;
		}
	}
	return p;
}

void Game::selectChess(int& enterCount)
{
	enterCount++;
	if (enterCount == 2) //push_enter_twice
	{
		//TODO: move()   
		enterCount = 0;
	}
	else //push_enter_once
	{
		Game::lastPosition = Game::chessMarkPosition;
		//TODO: whereCanEat(),whereCanGo() 
	}
}

/*
intent: get all red chesses position
pre:	null
post:	vector<Position>	----List of position of red chesses
*/
vector<Position> Game::getAllRedPosition()
{
	vector<Position> res;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (Game::board[i][j].typeID > 7)
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
vector<Position> Game::getAllBlackPosition()
{
	vector<Position> res;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (Game::board[i][j].typeID < 8)
			{
				res.push_back(Position(j, i));
			}
		}
	}
	return res;
}