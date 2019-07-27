#ifndef STATE_H
#define STATE_H

#include <memory>

class Piece;

enum class StateType {PieceAdded, PieceRemoved, Relay, Reply};
enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
	StateType type;
	Direction direction;
	bool attacked;
	shared_ptr<Piece> piece;
};
#endif
