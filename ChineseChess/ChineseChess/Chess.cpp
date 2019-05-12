#include <string>
#include "Chess.h"

using namespace std;

string Chess::showArray = "　將士象車馬包卒帥仕相俥傌炮兵";

/*
intent: constructor of Chess
pre: 
	int -----chessTypeID
post: null
*/
Chess::Chess(int typeID)
{
	//COMPLETED: use typeID to get the show string
	Chess::colour = typeID > 7;
	Chess::typeID = typeID;
	Chess::show = Chess::showArray.substr(typeID * 3, 3);
}
