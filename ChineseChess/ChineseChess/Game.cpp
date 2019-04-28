#include "Game.h"
#include <iostream>

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

void Game::newGame()
{
	//TODO: To initialize the board of game
}

void Game::lastGame()
{
	//TODO: To read file and set up the board of game
}
