#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm> 
#include "square.h"
#include "window.h"
#include "move.h"
using namespace std;

class Player;

class Board {
	vector<vector<Square>> defSquares;
	vector<int> whiteCounts;
	vector<int> blackCounts;
	bool defWhitesTurn;
	vector<vector<Square>> squares;
	Xwindow window;
	shared_ptr<Player> player1;
	shared_ptr<Player> player2;
	bool whitesTurn;
	double whiteScore;
	double blackScore;
	int moves; 

	// private methods
	Board(vector<vector<Square>>);
	void drawPiece(shared_ptr<Piece> piece);
	void undrawPiece(int r, int c);
	void printDefault();
	public:
		Board();
		void drawMenu();
		void drawBoard();
		void drawScore();
		void drawTurn();
		void drawSetupMenu();
		void setPlayer(string colour, string type);
		void init();
		void setup();
		string whoWon();
		void incScore(double w, double b);
		pair<double,double> getScore();
		bool isWhitesTurn();
		pair<int,int> getAttacks(int r, int c);
		void makePlayerMove();
		void generatePlayerMoves(bool white);
		void movePiece(int curR, int curC, int newR, int newC, char promoteTo);
		Move isLegalMove(shared_ptr<Piece> curPiece, int newR, int newC);
		void updateTurn(int curR, int curC, int newR, int newC, shared_ptr<Piece> piece, bool updateDraw);
		friend ostream & operator<<(ostream &out, const Board &b); 
};

#endif
