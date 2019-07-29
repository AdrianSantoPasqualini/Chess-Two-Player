#include "player.h"
#include "piece.h"
#include "board.h"
#include "info.h"
using namespace std;

Player::Player(bool isWhite): isWhite {isWhite} {
	score = 0;	
}

bool Player::isInCheck() const {
	bool check = false;
	pair<int, int> coor;
	if (isWhite) {
		coor = pieces.find("K")->second->getCoor();
		Info info = board->getSquare(coor.first, coor.second)->getInfo();
		if (info.wAttacked) {
			check = true;
		}
	} else {
		coor = pieces.find("k")->second->getCoor();
		Info info = board->getSquare(coor.first, coor.second)->getInfo();
		if (info.bAttacked) {
			check = true;
		}
	}
	return check;
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
