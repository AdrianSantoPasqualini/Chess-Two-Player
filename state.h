#ifndef STATE_H
#define STATE_H

class Piece;

enum class StateType {Relay, Reply};
enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
	StateType type;
	Direction direction;
	bool attacked;
	shared_ptr<Piece> piece;
};
#endif
