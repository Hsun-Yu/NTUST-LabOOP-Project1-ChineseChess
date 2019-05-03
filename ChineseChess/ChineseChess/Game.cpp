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
					Game::chessMarkPosition = Position(i, j);
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
					Game::chessMarkPosition = Position(i, j);
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
	
	//TODO: For test !!!!!!!
	//cin >> number;
	number = 1;
	
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

	setTextStyle(WHITE, BLACK);
	setCursorXY(0, 26);
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
	vector<Position> allRedPosition;
	allRedPosition = Game::getAllRedPosition();
	vector<Position> allBlackPosition;
	allBlackPosition = Game::getAllBlackPosition();

	vector<vector<int>> data(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 2)); //nochess = 2
	for(int i = 0 ; i < BOARD_HEIGHT ; i++)
	{
		for(int j = 0 ; j < BOARD_WIDTH ; j++)
		{
			for(int k = 0 ; k < allRedPosition.size() ; k++)
			{
				if(allRedPosition[k].x == j && allRedPosition[k].y == i)
						data[i][j] = 0; //red = 0
			}
			for(int l = 0 ; l < allBlackPosition.size() ; l++)
			{
				if(allBlackPosition[l].x == j && allBlackPosition[l].y == i)
						data[i][j] = 1; //black = 1
			}
		}
	}

	int enterCount = 0;

	while (1)
	{
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
			c = _getch();
			switch (c)
			{
			case 72:
				Game::chessMarkPosition = Up(data); //Up
				break;
			case 80:
				Game::chessMarkPosition = Down(data); //Down
				break;
			case 75:
				Game::chessMarkPosition = Left(data); //Left
				break;
			case 77:
				Game::chessMarkPosition = Right(data); //Right
				break;
			default: 
				break;
			}
		}
	}
}

Position Game::Up(vector<vector<int>> data)
{
	if(Game::chessMarkPosition.y == 0) //hit ceiling
		return Game::chessMarkPosition;
	else
	{
		Game::chessMarkPosition.y--;
		for (int i = Game::chessMarkPosition.y; i >= 0; i--)
		{
			if(data[Game::chessMarkPosition.x][i] == Game::whoPlay)
			{
				Game::chessMarkPosition.y = i;
				return Game::chessMarkPosition;
			}
		}
		if((Game::chessMarkPosition.x + 1) >= BOARD_WIDTH)
			return Game::chessMarkPosition;
		else
		{
			for(int i = Game::chessMarkPosition.x + 1 ; i < BOARD_WIDTH ; i++)
			{
				for(int j = 0 ; j < BOARD_HEIGHT ; j++)
				{
					if(data[i][j] == Game::whoPlay)
					{
						Game::chessMarkPosition.x = i;
						Game::chessMarkPosition.y = j;
						return Game::chessMarkPosition;
					}
				}
			}
			return Game::chessMarkPosition;	//if nothing can find		
		}
	}
}

Position Game::Down(vector<vector<int>> data)
{
	if(Game::chessMarkPosition.y == BOARD_HEIGHT - 1) //hit floor
		return Game::chessMarkPosition;
	else
	{
		Game::chessMarkPosition.y++;
		for (int i = Game::chessMarkPosition.y; i < BOARD_HEIGHT ; i++)
		{
			if(data[Game::chessMarkPosition.x][i] == Game::whoPlay)
			{
				Game::chessMarkPosition.y = i;
				return Game::chessMarkPosition;
			}
		}
		if((Game::chessMarkPosition.x + 1) >= BOARD_WIDTH)
			return Game::chessMarkPosition;
		else
		{
			for(int i = Game::chessMarkPosition.x + 1 ; i < BOARD_WIDTH ; i++)
			{
				for(int j = BOARD_HEIGHT - 1 ; j >= 0 ; j--)
				{
					if(data[i][j] == Game::whoPlay)
					{
						Game::chessMarkPosition.x = i;
						Game::chessMarkPosition.y = j;
						return Game::chessMarkPosition;
					}
				}
			}
			return Game::chessMarkPosition;	//if nothing can find
		}
	}
}

Position Game::Left(vector<vector<int>> data)
{
	if(Game::chessMarkPosition.x == 0) //hit leftwall
		return Game::chessMarkPosition;
	else
	{
		Game::chessMarkPosition.x--;
		for (int i = Game::chessMarkPosition.x; i >= 0 ; i--)
		{
			if(data[i][Game::chessMarkPosition.y] == Game::whoPlay)
			{
				Game::chessMarkPosition.x = i;
				return Game::chessMarkPosition;
			}
		}
		if((Game::chessMarkPosition.y - 1) < 0)
			return Game::chessMarkPosition;
		else
		{
			for(int i = Game::chessMarkPosition.y - 1 ; i >= 0 ; i--)
			{
				for(int j = 0 ; j < BOARD_WIDTH ; j++)
				{
					if(data[i][j] == Game::whoPlay)
					{
						Game::chessMarkPosition.x = i;
						Game::chessMarkPosition.y = j;
						return Game::chessMarkPosition;
					}
				}
			}
			return Game::chessMarkPosition;	//if nothing can find		
		}		
	}
}

Position Game::Right(vector<vector<int>> data)
{
	if(Game::chessMarkPosition.x == BOARD_WIDTH - 1) //hit rightwall
		return Game::chessMarkPosition;
	else
	{
		Game::chessMarkPosition.x++;
		for (int i = Game::chessMarkPosition.x; i < BOARD_WIDTH ; i++)
		{
			if(data[i][Game::chessMarkPosition.y] == Game::whoPlay)
			{
				Game::chessMarkPosition.x = i;
				return Game::chessMarkPosition;
			}
		}
		if((Game::chessMarkPosition.x + 1) >= BOARD_WIDTH)
			return Game::chessMarkPosition;
		else
		{
			for(int i = Game::chessMarkPosition.y - 1 ; i >= 0 ; i--)
			{
				for(int j = BOARD_WIDTH- 1 ; j >= 0 ; j--)
				{
					if(data[i][j] == Game::whoPlay)
					{
						Game::chessMarkPosition.x = i;
						Game::chessMarkPosition.y = j;
						return Game::chessMarkPosition;
					}
				}
			}
			return Game::chessMarkPosition;	//if nothing can find		
		}
	}
}
void Game::selectChess(int& enterCount)
{
	enterCount++;
	if (enterCount == 2) //push_enter_twice
	{
		///move()   TODO
		enterCount = 0;
	}
	else //push_enter_once
	{
		Game::lastPosition = Game::chessMarkPosition;
		//whereCanEat(),whereCanGo() TODO
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
				res.push_back(Position(i, j));
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
				res.push_back(Position(i, j));
			}
		}
	}
	return res;
}