#include <iostream>
#include <string>

using namespace std;

int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Board board;
  try {
    while (true) {
      cin >> cmd;
      if (cmd == "game") {
        string p1, p2;
        cmd >> p1;
        cmd >> p2; 
        board.init();
      }
      else if (cmd == "resign") {
        //resign
      }
      else if (cmd == "move") {
        //move
      }
      else if (cmd == "setup") {
        //setup
        //user cannot leave setup mode until conditions are met
      }
    }
  }
}
