#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
////////////////////////////////
// try forward declarations first. Only if they dont work, include the .h file
///////////////////////////////
using namespace std;

class Square;

class Board {
	vector<vector<Square>> squares;
	//Xwindow window;
	//Player player1;
	//Player player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;

	public:
		//~Board();
		void init(string playerOne, string playerTwo);
		void setup();
		int whoWon();
		friend ostream & operator<<(ostream &out, const Board &b); 
};

#endif
