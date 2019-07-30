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
	board.drawMenu();
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
				board.drawBoard();
				board.drawScore();
				board.drawTurn();
				board.setPlayer("white", p1);
				board.setPlayer("black", p2);
				matchOngoing = true;
			} else {
				cout << "Invalid players." << endl;
			}
			if (matchOngoing) {
				cout << board;
			}
		} else if (cmd == "resign" && matchOngoing) {
			if (board.isWhitesTurn()){
				board.incScore(0, 1);
				cout << "Black wins!" << endl;
			} else {
				board.incScore(1, 0);
				cout << "White wins!" << endl;
			} 
			cout << "Would you like to play another round? (y/n)" << endl;
			string response;
			cin >> response;
			bool continuing;
			while(true) {
				if (response == "y" || response == "yes" || response == "Y" || response == "Yes") {
					board.init();
					board.drawBoard();
					board.drawScore();
					cout << board;
					continuing = true;
					break;
				} else if (response == "n" || response == "no" || response == "N" || response == "No") {
					continuing = false;
					break;
				} else {
					cin >> response;
				}
			}
			if (!continuing) {
				break;
			}
		} else if (cmd == "move" && matchOngoing) {
			board.makePlayerMove();
			board.drawScore();
			board.drawTurn();
			cout << board;
			if (board.isWhitesTurn()) {
				board.generatePlayerMoves(true);
			} else {
				board.generatePlayerMoves(false);
			}
			string winner = board.whoWon();
			if (winner == "white") {
				board.incScore(1, 0);
				cout << "Checkmate! White Wins!" << endl;
			} else if (winner == "black") {
				board.incScore(0, 1);
				cout << "Checkmate! Black Wins!" << endl;
			} else if (winner == "stalemate") {
				board.incScore(0.5, 0.5);
				cout << "Stalemate!" << endl;
			}
			if (winner != "noone") {
				cout << "Would you like to play another round? (y/n)" << endl;
				string response;
				cin >> response;
				bool continuing;
				while(true) {
					if (response == "y" || response == "yes" || response == "Y" || response == "Yes") {
						board.init();
						board.drawBoard();
						board.drawScore();
						cout << board;
						continuing = true;
						break;
					} else if (response == "n" || response == "no" || response == "N" || response == "No") {
						continuing = false;
						break;
					} else {
						cin >> response;
					}
				}
				if (!continuing) {
					break;
				}
			}
		} else if (cmd == "setup" && !matchOngoing) {
			board.setup();
		}
	} 
	cout << "Final Score:" << endl;
	cout << "White: " << board.getScore().first << endl;
	cout << "Black: " << board.getScore().second << endl;
}

