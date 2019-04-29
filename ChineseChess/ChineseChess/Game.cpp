#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game()
{
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
	default:
		return false;
		break;
	case 1:
		newGame();
		break;
	case 2:
		lastGame();
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
	//initial example
	//4 5 3 2 1 2 3 5 4
	//0 0 0 0 0 0 0 0 0
	//0 6 0 0 0 0 0 6 0
	//7 0 7 0 7 0 7 0 7
	//0 0 0 0 0 0 0 0 0
	//0 0 0 0 0 0 0 0 0
	//14 0 14 0 14 0 14 0 14
	//0 13 0 0 0 0 0 13 0
	//0 0 0 0 0 0 0 0 0
	//11 12 10 9 8 9 10 12 11
	//1

	//COMPLETED: To initialize the board of game

	Game::whoPlay = Game::board.readBoardFile("Chessboard/Initial.txt");
}

/*
intent: read file to board
pre: null
post: null
*/
void Game::lastGame()
{
	//COMPLETED: To read file and set up the board of game
	
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
