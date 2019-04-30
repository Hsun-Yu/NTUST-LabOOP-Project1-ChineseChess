#include "Board.h"

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

