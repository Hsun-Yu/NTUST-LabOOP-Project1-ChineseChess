#include "Board.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

#pragma once
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
private:
	Board board;
	bool whoPlay;	//red true, black false
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// ¶Â¥Õ¬õºñÂÅ«Cµµ
	int textColors[7] = {
		0,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		FOREGROUND_RED, 
		FOREGROUND_GREEN, 
		FOREGROUND_BLUE,
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY  
	};
};

