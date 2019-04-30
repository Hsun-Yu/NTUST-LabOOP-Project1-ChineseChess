#include "Board.h"
#include <iostream>
#include <fstream>

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

	//TODO (Even): do display
	void display();
private:
	Board board;
	bool whoPlay;	//red true, black false
};

