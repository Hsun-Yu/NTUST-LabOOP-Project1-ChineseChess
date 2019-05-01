#include "Board.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

#define BLACK 0
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define PURPLE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY

class Game
{
public:
	Game();
	~Game();

	void initialize();
	bool getInitialType();
	void newGame();
	void lastGame();
	
	void display();

	void setTextStyle(int color, int backgroundColor);
	void saveGame(string);
private:
	Board board;
	bool whoPlay;	//red true, black false
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
};

