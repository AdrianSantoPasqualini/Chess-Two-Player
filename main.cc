#include <iostream>
#include <string>
#include <algorithm>
#include "board.h"
#include "player.h"
using namespace std;

int main() {
	cin.exceptions(ios::eofbit|ios::failbit);
 	Board board;
	bool matchOngoing = false;
	vector<string> players = {"human", "computer1", "computer2", "computer3", "computer4"};
 	string cmd;
	while (!cin.eof()) {
		if (matchOngoing && board.isWhitesTurn()) {
			cout << "White to move." << endl;
		} else if (matchOngoing && !board.isWhitesTurn()) {
			cout << "Black to move." << endl;
		}
		cin >> cmd;
		if (cmd == "game" && !matchOngoing) {
			string p1, p2;
			cin >> p1 >> p2;
			vector<string>::iterator it1, it2;
			it1 = find(players.begin(), players.end(), p1);
			it2 = find(players.begin(), players.end(), p2);
			if (it1 != players.end() && it2 != players.end()) {
				board.init();
				board.setPlayer("white", p1);
				board.setPlayer("black", p2);
				matchOngoing = true;
				cout << board;
			} else {
				cout << "Invalid players." << endl;
			}
		} else if (cmd == "resign" && matchOngoing) {
			if (board.isWhitesTurn()){
				board.incBlackScore();
				cout << "Black wins!" << endl;
			} else {
				board.incWhiteScore();
				cout << "White wins!" << endl;
			} 
			matchOngoing = false;
		} else if (cmd == "move" && matchOngoing) {
			string c1, c2;
			cin >> c1 >> c2;
			board.movePiece('8' - c1[1], c1[0] - 'a', '8' - c2[1], c2[0] - 'a');
		} else if (cmd == "setup" && !matchOngoing) {
			board.setup();
		} else {
			cout << "Invalid command." << endl;
		}
	} 
	cout << "Final Score:" << endl;
	cout << "White: " << board.getWhiteScore() << endl;
	cout << "Black: " << board.getBlackScore() << endl;
}

