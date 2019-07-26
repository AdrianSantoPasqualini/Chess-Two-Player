#include "player.h"
#include "piece.h"
using namespace std;

Player::Player(bool isWhite): isWhite {isWhite} {
	score = 0;	
}

bool Player::isInCheck() const {
	return false;
}

void Player::addPiece(shared_ptr<Piece> p) {
	// is the string in pieces the id of piece?
	pieces.emplace(p->getId(), p);
}

void Player::removePiece(string id) {
	pieces.erase(id);
}


Human::Human(bool isWhite): Player{isWhite} {}

void Human::makeMove() {

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
