#include <string>

using namespace std;

#pragma once
class Chess
{
public:
	Chess(int);

	int typeID;		// see showArray
	bool colour;	// black is true, red is false
	string show;	// the word will show on the board

private:
	static string showArray;	// save the word with the order of typeID
};

