#include "Game.h"

using namespace std;

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;
string Game::road[2][9] = {
		{"１" ,"２" ,"３" ,"４" ,"５" ,"６" ,"７" ,"８" ,"９"},
		{"九" , "八" , "七" , "六" , "五" , "四" , "三" , "二" , "一"}
};

Game::Game()
{
	Game::initialize();
	Game::display();
	Game::inGame();
	Game::endOfGame();
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
	system("cls");

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
	PlaySound("Music\\background_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
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
int Game::menu()
{
	system("cls");
	int num;

	cout << "1.繼續遊戲" << endl;
	cout << "2.重新開始" << endl;
	cout << "3.回主選單" << endl;
	cout << "4.離開遊戲" << endl;
	cout << "Input number:" << endl;

	while (1)
	{
		cin >> num;
		if (num == 1)
		{
			Game::display();
		}
		else if (num == 2)
		{
			Game::initialize();
			Game::display();
		}
		else if (num == 3)
		{
			Game::saveGame("Chessboard\\LastGame.txt");
			Game::initialize();
			Game::display();
		}
		else if (num == 4)
		{
			system("cls");
			return 1;
		}
		else
		{
			cout << "Please input the correct number: " << endl;
			continue;
		}
		break;
	}

	return 0;
}

/*
intent: Logging game.
pre: 
	che: Moveing chess.
	from: From position.
	to: To position.
pre: void.
*/
void Game::gameLog(Chess che, Position from, Position to)
{
	string str;
	int sameChess = 0, thisChessOrder = 0;

	str = che.colour ? "紅 : " : "黑 : ";

	// Check how many chess behind it.
	for (int i = 0; i < 10; i++)
	{
		if (board[i][from.x].typeID == che.typeID)
		{
			if (i == from.y)
			{
				thisChessOrder = sameChess;
			}
			sameChess++;
		}
	}

	if (che.colour) thisChessOrder = sameChess - 1 - thisChessOrder;

	// First two words. 
	// If the road only has one chess or chess is 士, 象, 仕, 相.
	if (sameChess == 1 || che.typeID == 2 || che.typeID == 3 || che.typeID == 9 || che.typeID == 10)
	{
		str += che.show;
		str += Game::road[che.colour][from.x];
	}
	else
	{
		string orderString[4][5] = {
			{"後", "前"},
			{"後", "中", "前"},
			{"後", "三", "二", "前"},
			{"後", "四", "三", "二", "前"},
		};
		
		for (int i = sameChess - 1; i >= 0; i--)
		{
			if (thisChessOrder == i)
			{
				str += orderString[sameChess - 2][i];
				break;
			}
		}
		
		str += che.show;
	}
	
	// Last two words.
	if (to.y == from.y)
	{
		str += "平";
		str += Game::road[che.colour][to.x];
	}
	else 
	{
		str += che.colour ^ (to.y > from.y) ? "進" : "退";

		if (to.x == from.x)
		{
			str += Game::road[che.colour][che.colour ? 8 - (abs(to.y - from.y) - 1) : abs(to.y - from.y) - 1];
		}
		else
		{
			str += Game::road[che.colour][che.colour ? to.x : to.x];
		}
	}

	if (Game::boardHistoryIndex < Game::situation.size())
	{
		Game::situation[Game::boardHistoryIndex] = str;
		for (int i = Game::boardHistoryIndex + 1; i < Game::situation.size();)
			Game::situation.erase(Game::situation.begin() + i);
	}
	else
		Game::situation.push_back(str);
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

	Game::setTextStyle(WHITE, BLACK);
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

	// Output board.
	setTextStyle(BLACK, KHIKI);
	for (int i = 0; i <= 20; i++)
	{
		if (i == 1) setTextStyle(BLACK, KHIKI);
		if (i == 20) setTextStyle(BLACK, KHIKI);
		Game::setCursorXY(24, i + 1);
		cout << boardRows[i];
	}

	// Put chesses to board.
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

	// Output game log.
	setTextStyle(WHITE, BLACK);

	int num = 0;
	int situCount = Game::boardHistoryIndex;
	for (int i = situCount > 18 ? situCount - 18 : 0; i < situCount; i++, num++)
	{
		Game::setCursorXY(4, 3 + num);
		cout.width(3);
		cout << i + 1 << " ";
		if (Game::situation[i].substr(0, 3) == "黑")
		{
			setTextStyle(BLACK2, BLACK);
			cout << "黑";
		}
		else
		{
			setTextStyle(RED, BLACK);
			cout << "紅";
		}
		setTextStyle(WHITE, BLACK);
		cout << Game::situation[i].substr(3);
	}

	if (Game::board.check(Game::whoPlay))	//Check is Check
		Game::showCheckmate(Game::whoPlay);

	if (Game::checkLose(Game::whoPlay))
		isInGame = false;

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

	setTextStyle(WHITE, BLACK);
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
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = true;
	lpCursor.dwSize = 10;
	SetConsoleCursorInfo(Game::outputHandle, &lpCursor);
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

void Game::saveBoard()
{
	Game::boardHistoryIndex++;
	if (Game::boardHistoryIndex < Game::boardHistory.size())
	{
		Game::boardHistory[Game::boardHistoryIndex] = Game::board;
		for (int i = boardHistoryIndex + 1; i < Game::boardHistory.size();)
			Game::boardHistory.erase(Game::boardHistory.begin() + i);
	}
	else
		Game::boardHistory.push_back(Game::board);
}

/*
intent: Change text style
pre: null
post: void.
*/
void Game::inGame()
{
	saveBoard();
	isInGame = true;
	while (isInGame)
	{
		showWhoPlay();

		Game::setCursorBoardXY(Game::chessMarkPosition);
		vector<Position> allRedPosition;
		allRedPosition = Game::board.getAllRedPosition();
		vector<Position> allBlackPosition;
		allBlackPosition = Game::board.getAllBlackPosition();
		vector<Position> objPosition;

		char c = 0;
		c = _getch();
		if (c == 13) //Enter
		{
			showNowChess();
			selectChess();
		}
		else if (c == 27) //esc
  		{
			if (Game::menu()) return;
		}
  		else if (c == 44) //<
  		{
			if (Game::boardHistoryIndex - 1 >= 0)
			{
				Game::board = Game::boardHistory[--Game::boardHistoryIndex];
				Game::whoPlay = !Game::whoPlay;
				Game::resetMarkPosition();
				Game::display();
			}
  		}
  		else if (c == 46) //>
  		{
			if (Game::boardHistoryIndex + 1 < Game::boardHistory.size())
			{
				Game::board = Game::boardHistory[++Game::boardHistoryIndex];
				Game::whoPlay = !Game::whoPlay;
				Game::resetMarkPosition();
				Game::display();
			}
  		}
		else
		{

			if (whoPlay)
			{
				objPosition = allRedPosition;
			}
			else
			{
				objPosition = allBlackPosition;
			}
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

	//vector<Position> eatD = Game::board.canNotGoFilter(Game::whoPlay, Game::lastPosition, eat);
	//vector<Position> goD = Game::board.canNotGoFilter(Game::whoPlay, Game::lastPosition, go);

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

	vector<Position> mixD = Game::board.canNotGoFilter(Game::whoPlay, Game::lastPosition, mix);

	vector<Position> suicide;

	for (int i = 0; i < mix.size(); i++)
	{
		bool ch = false;
		for (int j = 0; j < mixD.size(); j++)
		{
			if (mixD[j].x == mix[i].x && mixD[j].y == mix[i].y)
			{
				ch = true;
				break;
			}
		}

		if (!ch)
		{
			markOnScreen(mix[i], PURPLE);
			suicide.push_back(mix[i]);
		}
	}

	if (mix.size() != 0)
		Game::chessMarkPosition = mix[0];
	else
	{
		Game::display();
		return;
	}

	
	Game::setCursorBoardXY(Game::chessMarkPosition);

	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			for (int i = 0; i < suicide.size(); i++)
			{
				if (chessMarkPosition.x == suicide[i].x && chessMarkPosition.y == suicide[i].y)
				{
					PlaySound(TEXT("Music\\suicide_sound.wav"), NULL, SND_SYNC);
				}
			}
			Game::move(Game::lastPosition, Game::chessMarkPosition);
			Game::display();
			return;
		}
		else if (c == 8) //Backspace
		{
			//back to inGame
			Game::chessMarkPosition = Game::lastPosition;
			Game::display();
			return;
		}
		else if (c == 27) //esc
		{
			Game::menu(); return;
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
	Game::gameLog(Game::board[lastPosition.y][lastPosition.x], lastPosition, newPosition);
	Game::board = Game::board.move(lastPosition, newPosition);

	Game::whoPlay = !Game::whoPlay;
	Game::resetMarkPosition();

	Game::saveBoard();

	Game::setTextStyle(WHITE, BLACK);
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

bool Game::checkLose(bool whoPlay)
{
	vector<Position> mix;//eat and go
	vector<Position> allChessPosition;

	if (whoPlay)		//red
		allChessPosition = Game::board.getAllRedPosition();
	else	//black
		allChessPosition = Game::board.getAllBlackPosition();

	for (int i = 0; i < allChessPosition.size(); i++)
	{
		vector<Position> eat = Game::board.whereCanEat(allChessPosition[i]);
		vector<Position> go = Game::board.whereCanGo(allChessPosition[i]);

		eat = Game::board.canNotGoFilter(Game::whoPlay, allChessPosition[i], eat);
		go = Game::board.canNotGoFilter(Game::whoPlay, allChessPosition[i], go);

		for (int j = 0; j < eat.size(); j++)
			mix.push_back(eat[j]);

		for (int j = 0; j < go.size(); j++)
			mix.push_back(go[j]);
	}

	if (mix.size() == 0)
		return true;
	else
	{
		for (int i = 0; i < allChessPosition.size(); i++)
		{
			if (Game::board[allChessPosition[i].y][allChessPosition[i].x].typeID % 7 == 1)
				return false;
		}

		return true;
	}

}

void Game::showWhoPlay()
{
	Game::setCursorXY(72,3);
	cout.width(3);
	if (whoPlay)
	{
		setTextStyle(RED, BLACK);
		cout << "紅色方";
	}
	else
	{
		setTextStyle(BLACK2, BLACK);
		cout << "黑色方";
	}
	setTextStyle(WHITE, BLACK);
}

void Game::showNowChess()
{
	int chessTypeID = board[chessMarkPosition.y][chessMarkPosition.x].typeID;

	Game::setCursorXY(75,6);
	cout.width(3);
	if (whoPlay)
	{
		setTextStyle(RED, BLACK);
		if (chessTypeID == 8)
			cout << "帥";
		else if (chessTypeID == 9)
			cout << "仕";
		else if (chessTypeID == 10)
			cout << "相";
		else if (chessTypeID == 11)
			cout << "車";
		else if (chessTypeID == 12)
			cout << "傌";
		else if (chessTypeID == 13)
			cout << "炮";
		else if (chessTypeID == 14)
			cout << "兵";
	}
	else
	{
		setTextStyle(BLACK2, BLACK);
		if (chessTypeID == 1)
			cout << "將";
		else if (chessTypeID == 2)
			cout << "士";
		else if (chessTypeID == 3)
			cout << "象";
		else if (chessTypeID == 4)
			cout << "車";
		else if (chessTypeID == 5)
			cout << "馬";
		else if (chessTypeID == 6)
			cout << "包";
		else if (chessTypeID == 7)
			cout << "卒";
	}
	setTextStyle(WHITE, BLACK);

}

void Game::showCheckmate(bool whoCheckmate)
{
	Game::setCursorXY(69, 9);
	cout.width(5);
	if (whoCheckmate)
	{
		setTextStyle(RED, BLACK);
		cout << "紅方被將軍";
		
		vector<Position> v = Game::board.getAllBlackPosition();
		
		for (int i = 0; i < v.size(); i++)
		{
			vector<Position> eat = Game::board.whereCanEat(v[i]);
			for (int j = 0; j < eat.size(); j++)
			{
				if (Game::board[eat[j].y][eat[j].x].typeID % 7 == 1)
					Game::markOnScreen(v[i], LIGHTRED);
			}
		}
		
	}
	else
	{
		setTextStyle(BLACK2, BLACK);
		cout << "黑方被將軍";

		vector<Position> v = Game::board.getAllRedPosition();

		for (int i = 0; i < v.size(); i++)
		{
			vector<Position> eat = Game::board.whereCanEat(v[i]);
			for (int j = 0; j < eat.size(); j++)
			{
				if (Game::board[eat[j].y][eat[j].x].typeID % 7 == 1)
					Game::markOnScreen(v[i], LIGHTRED);
			}
		}
	}
	setTextStyle(WHITE, BLACK);
}

void Game::endOfGame()
{
	system("cls");
	if (whoPlay)
		cout << "黑方勝" << endl;
	else
		cout << "紅方勝" << endl;

	cout << "1.回放" << endl;
	cout << "2.重新開始" << endl;

	int in;
	while (1)
	{
		cin >> in;
		if (in == 1)
		{
			while (1)
			{
				Game::display();

				char c = _getch();
				if (c == 27) //esc
				{
					return;
				}
				else if (c == 44) //<
				{
					if (Game::boardHistoryIndex - 1 >= 0)
					{
						Game::board = Game::boardHistory[--Game::boardHistoryIndex];
						Game::display();
					}
				}
				else if (c == 46) //>
				{
					if (Game::boardHistoryIndex + 1 < Game::boardHistory.size())
					{
						Game::board = Game::boardHistory[++Game::boardHistoryIndex];
						Game::display();
					}
				}
			}
		}
		else if (in == 2)
		{
			Game::initialize();
			break;
		}
	}
}
