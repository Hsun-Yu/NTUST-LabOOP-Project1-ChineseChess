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

	Game::resetMarkPosition();
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
	intent: click ESC to call game menu.
	pre: void.
	post: void.
*/
void Game::menu()
{

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

/*
intent: display
pre: void
post: void
*/
void Game::display()
{
	system("cls");
	ifstream inputS("Chessboard\\board_template.txt");
	string str;
	vector<string> boardRows;

	while (getline(inputS, str))
	{
		cout << str << endl;
	}

	inputS.close();

	// Board start in (24, 2) (黑車)
	boardRows = {
		"１　２　３　４　５　６　７　８　９",
		"－－－－－－－－－－－－－－－－－",
		"｜　｜　｜　｜＼｜／｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜／｜＼｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜　｜　｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜　｜　｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　　　楚河　　　　　漢界　　　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜　｜　｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜　｜　｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜＼｜／｜　｜　｜　｜",
		"｜－＋－＋－＋－＋－＋－＋－＋－｜",
		"｜　｜　｜　｜／｜＼｜　｜　｜　｜",
		"－－－－－－－－－－－－－－－－－",
		"九　八　七　六　五　四　三　二　一"
	};

	setTextStyle(PURPLE, WHITE);
	for (int i = 0; i <= 20; i++)
	{
		if (i == 1) setTextStyle(BLACK, WHITE);
		if (i == 20) setTextStyle(PURPLE, WHITE);
		Game::setCursorXY(24, i + 1);
		cout << boardRows[i];
	}

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

/*
intent: Change text style
pre:
	int x
	int y
post: void.
*/
void Game::setCursorXY(int x, int y)
{
	Game::cursorXY.X = x;
	Game::cursorXY.Y = y;
	SetConsoleCursorPosition(Game::outputHandle, Game::cursorXY);
}

/*
intent: Change text style
pre:
	Position	----position on board
post: void.
*/
void Game::setCursorBoardXY(Position pos)
{
	Game::setCursorXY(24 + pos.x * 4, 2 + pos.y * 2);
}

//void Game::moveCursor(int x, int y)
//{
//	Game::setCursorXY(Game::cursorXY.X + x, Game::cursorXY.Y + y);
//}

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

/*
intent: Change text style
pre: null
post: void.
*/
void Game::inGame()
{
	int enterCount = 0;

	while (1)
	{
		Game::setCursorBoardXY(Game::chessMarkPosition);
		vector<Position> allRedPosition;
		allRedPosition = Game::getAllRedPosition();
		vector<Position> allBlackPosition;
		allBlackPosition = Game::getAllBlackPosition();
		vector<Position> objPosition;

		char c = 0;
		c = _getch();
		if (c == 13) //Enter
		{
			selectChess();
		}
		else if (c == 27) //esc
  		{
			//TODO (Even):menu
		}
  		else if (c == 44) //<
  		{
      		//TODO : ??
      		cout << "<" <<endl;
  		}
  		else if (c == 46) //>
  		{
      		//TODO : ??
      		cout << ">" <<endl;
  		}
		else
		{

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

/*
intent:	to select chess
pre: null
post: void
*/
void Game::selectChess()
{
	Game::lastPosition = Game::chessMarkPosition;
	vector<Position> eat = Game::board.whereCanEat(Game::chessMarkPosition);
	vector<Position> go = Game::board.whereCanGo(Game::chessMarkPosition);

	vector<Position> mix;//eat and go
	for (int i = 0; i < go.size(); i++)
	{
		markOnScreen(go[i], BLUE);
		mix.push_back(go[i]);
	}

	for (int i = 0; i < eat.size(); i++)
	{
		markOnScreen(eat[i], GREEN);
		mix.push_back(eat[i]);
	}

	if (mix.size() != 0)
		Game::chessMarkPosition = mix[0];
	else
		return;
	
	Game::setCursorBoardXY(Game::chessMarkPosition);

	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::move(Game::lastPosition, Game::chessMarkPosition);
			Game::display();
			return;
		}
		else if (c == 8) //Backspace
		{
			//back to inGame
			return;
		}
		else if (c == 27) //esc
		{
			//TODO (Even):menu
		}
		else
		{
			switch (c)
			{
			case 72:
				Game::chessMarkPosition = Up(mix); //Up
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 80:
				Game::chessMarkPosition = Down(mix); //Down
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 75:
				Game::chessMarkPosition = Left(mix); //Left
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			case 77:
				Game::chessMarkPosition = Right(mix); //Right
				Game::setCursorBoardXY(Game::chessMarkPosition);
				break;
			default:
				break;
			}
		}
	}
}

/*
intent: move chess
pre:	
	Position	----lastPosition
	Position	----newPosition
post:	void
*/
void Game::move(Position lastPosition, Position newPosition)
{
	Game::board[newPosition.y][newPosition.x] = Game::board[lastPosition.y][lastPosition.x];
	Game::board[lastPosition.y][lastPosition.x] = Chess(0);

	Game::whoPlay = !Game::whoPlay;
	Game::resetMarkPosition();
}

/*
intent: when change player we need to reset MarkPosition
pre: null
post: void
*/
void Game::resetMarkPosition()
{
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
			if (Game::board[i][j].typeID < 8 && Game::board[i][j].typeID > 0)
			{
				res.push_back(Position(j, i));
			}
		}
	}
	return res;
}