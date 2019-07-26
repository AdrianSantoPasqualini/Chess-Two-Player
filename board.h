#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "square.h"
////////////////////////////////
// try forward declarations first. Only if they dont work, include the .h file
///////////////////////////////
using namespace std;

class InvalidInput{};
class InvalidPawn{};

class Player;

class Board {
	vector<vector<Square>> defSquares;
	vector<int> whiteCounts;
	vector<int> blackCounts;
	bool defWhitesTurn;
	vector<vector<Square>> squares;
	//Xwindow window;
	unique_ptr<Player> player1;
	unique_ptr<Player> player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;

	// private methods
	int colToInt(char c);
	bool isValid(); // used in setup to check if specifications are met
	void printDefault();

	public:
		//~Board();
		Board();
		void setPlayer(string colour, string type);
		void init();
		void setup();
		int whoWon();
		void incWhiteScore();
		void incBlackScore();
		bool whiteTurn();
		
		friend ostream & operator<<(ostream &out, const Board &b); 
};

#endif
