#include <iostream>
#include <string>
#include "board.h"
#include "player.h"
using namespace std;

int main() {
	cin.exceptions(ios::eofbit|ios::failbit);
 	string cmd;
 	Board board;
	bool matchOngoing = false;
 	try {
		while (true) {
			if (matchOngoing && board.isWhitesTurn()) {
				cout << "White to move." << endl;
			} else if (matchOngoing && !board.isWhitesTurn()) {
				cout << "Black to move." << endl;
			}
			cin >> cmd;
			if (cmd == "game" && !matchOngoing) {
				string p1, p2;
				cin >> p1 >> p2; // check for human/computer
				board.init();
				// check for invalid inputs?
				board.setPlayer("white", p1);
				board.setPlayer("black", p2);
				matchOngoing = true;
				cout << board;
			} else if (cmd == "resign" && matchOngoing) {
				if (board.isWhitesTurn()){
					board.incBlackScore();	
				} else {
					board.incWhiteScore();
				} 
				matchOngoing = false;
			} else if (cmd == "move" && matchOngoing) {
				string c1, c2;
				cin >> c1 >> c2;
				board.movePiece('8' - c1[1], c1[0] - 'a', '8' - c2[1], c2[0] - 'a');
			} else if (cmd == "setup" && !matchOngoing) {
				bool done = false;
				while (!done){
					cin >> cmd;
					if (cmd == "+") {
						
					} else if (cmd == "-") {
						
					} else if (cmd == "=") {
						
					} else if (cmd == "done") {
							
					}
				}
			  //user cannot leave setup mode until conditions are met
			}
    		}
	} catch (ios::failure &) {
  		
	}
}

