#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

////////////////////////////////
// try forward declarations first. Only if they dont work, include the .h file
///////////////////////////////

class Player;
class Square;

using namespace std;

class Board {
	vector<vector<Square>> squares;
	//Xwindow window;
	Player player1;
	Player player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;

	public:
		~Grid();
		void init();
		void setup();
		int whoWon();
		friend ostream & operator<<(ostream &out, const Board &b); 
<<<<<<< HEAD
};

// Adrians Test edit
=======
}
// William Test
>>>>>>> de814fd986026622d5744f10d70f29090aa6fb45
#endif
