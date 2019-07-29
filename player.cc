#include "player.h"
#include "piece.h"
#include "board.h"
#include <ctime>    
#include <cstdlib>

using namespace std;





///////////////////////// HOW TO RANDOM ////////////////////////////
// srand(time(0)); // Sets the random seed based on the current time.
// r = (rand() % x); // Generates random number from 0 to x.
////////////////////////////////////////////////////////////////////


Player::Player(bool isWhite): isWhite {isWhite} {
	score = 0;	
}

bool Player::isInCheck() const {
	return false;
}

void Player::attachBoard(shared_ptr<Board> currBoard) {
	board = currBoard;
}


void Player::addPiece(shared_ptr<Piece> p) {
	pieces.emplace(p->getId(), p);
}

void Player::removePiece(string id) {
	pieces.erase(id);
}


Human::Human(bool isWhite): Player{isWhite} {}

void Human::makeMove() {
	string oldCoord;
	string newCoord;
	cin >> oldCoord >> newCoord;
	board->movePiece('8' - oldCoord[1], oldCoord[0] - 'a', '8' - newCoord[1], newCoord[0] - 'a');
}


Level1::Level1(bool isWhite): Player{isWhite} {}

void Level1::makeMove() {

}

Level2::Level2(bool isWhite): Player{isWhite} {}

void Level2::makeMove() {

}


Level3::Level3(bool isWhite): Player{isWhite} {}

void Level3::makeMove() {

}


Level4::Level4(bool isWhite): Player{isWhite} {}

void Level4::makeMove() {

}
