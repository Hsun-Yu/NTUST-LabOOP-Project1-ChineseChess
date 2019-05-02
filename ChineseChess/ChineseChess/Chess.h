#include <iostream>
#include <string>

using namespace std;

#pragma once
class Chess
{
public:
	Chess(int);

	int typeID;		// see showArray
	bool colour;	// black is false, red is true
	string show;	// the word will show on the board

private:
	static string showArray;	// save the word with the order of typeID
};

