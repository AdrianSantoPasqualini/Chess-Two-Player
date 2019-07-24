#ifndef PIECE_H
#define PIECE_H

// Relevant forward declarations and includes

class Piece {
	int row;
	int col;
	int movesMade;
	bool isWhite;
	string id;

	public: 
		Piece(int row, int col, string id, bool isWhite, int movesMade = 0);
		virtual void move(int r, int c) =0;
}


class Pawn: public Piece {
	bool specialAdvance;
	
	public:
		Pawn(int row, int col, string id, bool isWhite, int movesMade = 0, bool specialAdvance = false);
		void move(int r, int c) override;
}


class Knight: public Piece {
        public:
                Knight(int row, int col, string id, bool isWhite, int movesMade = 0);
                void move(int r, int c) override;
}


class Bishop: public Piece {
        public:
                Bishop(int row, int col, string id, bool isWhite, int movesMade = 0);
                void move(int r, int c) override;
}


class Rook: public Piece {
        public:
                Rook(int row, int col, string id, bool isWhite, int movesMade = 0);
                void move(int r, int c) override;
}


class Queen: public Piece {
        public:
                Queen(int row, int col, string id, bool isWhite, int movesMade = 0);
                void move(int r, int c) override;
}


class King: public Piece {
        public:
                King(int row, int col, string id, bool isWhite, int movesMade = 0);
                void move(int r, int c) override;
}

#endif
