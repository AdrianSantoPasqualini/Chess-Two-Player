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
	shared_ptr<Player> wPlayer;
	shared_ptr<Player> bPlayer;
	if (p1 == "human") {
		wPlayer = make_shared<Human>(true);
	} else if (p1 == "computer1") {
		wPlayer = make_shared<Level1>(true);
	} else if (p1 == "computer2") {
                wPlayer = make_shared<Level2>(true);
        } else if (p1 == "computer3") {
                wPlayer = make_shared<Level3>(true);
        } else if (p1 == "computer4") {
                wPlayer = make_shared<Level4>(true);
        }

	if (p2 == "human") {
                bPlayer = make_shared<Human>(false);
        } else if (p2 == "computer1") {
                bPlayer = make_shared<Level1>(false);
        } else if (p2 == "computer2") {
                bPlayer = make_shared<Level2>(false);
        } else if (p2 == "computer3") {
                bPlayer = make_shared<Level3>(false);
        } else if (p2 == "computer4") {
                bPlayer = make_shared<Level4>(false);
        }
	board.setPlayer("white", wPlayer);
	board.setPlayer("black", wPlayer);
        board.init();
	cout << board;
      }
      else if (cmd == "resign") {
        //resign
      }
      else if (cmd == "move") {

      }
      else if (cmd == "setup") {
        //setup
        //user cannot leave setup mode until conditions are met
      }
    }
  }
  catch (invalid_argument) {
	cout << "Why is this try catch block here again?" << endl;
  }
}
