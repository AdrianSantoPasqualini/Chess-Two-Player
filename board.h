#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

////////////////////////////////
// try forward declarations first here. Only if they dont work, include the .h file
///////////////////////////////

class Board {
	vector<vector<Square>> squares;
	//Xwindow window;
	Player player1;
	Player player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;

	public:
		void init();
		void setup();
		int whoWon();
}
#endif
