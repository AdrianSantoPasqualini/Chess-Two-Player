#include <iostream>
#include <string>
#include "board.h"
#include "player.h"
using namespace std;

int main() {
	cin.exceptions(ios::eofbit|ios::failbit);
 	string cmd;
 	Board board;
 	try {
    	while (true) {
      		cin >> cmd;
      		bool matchOngoing = false;
      		if (cmd == "game" && !matchOngoing) {
        		string p1, p2;
        		cin >> p1;
        		cin >> p2;
        		board.init();
			// check for invalid inputs?
			board.setPlayer("white", p1);
			board.setPlayer("black", p2);
			cout << board;
		}
      		else if (cmd == "resign" && matchOngoing) {
			matchOngoing = false;
			 
      		}
      		else if (cmd == "move" && matchOngoing) {
      		  //move
      		}
      		else if (cmd == "setup" && !matchOngoing) {
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
		catch(...) {
			//if user does something invalid
		}
	}
  	catch (ios::failure &) {
  	}
}

