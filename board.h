#ifndef BOARD_H__
#define BOARD_H__

#include <cstddef>
#include "bit_vector.h"
#include "board_position.h"
#include "board_direction.h"

class Board {
public:
	typedef BitVector<64,2> BoardVector;
	typedef BoardPosition<> BoardPosition;
	const uint_fast8_t Light = 0b10;
	const uint_fast8_t Dark = 0b11;

	Board() : whoseTurn(Dark) {
		theBoard.matrixPut(3,3,Dark);
		theBoard.matrixPut(4,3,Light);
		theBoard.matrixPut(3,4,Light);
		theBoard.matrixPut(4,4,Dark);
	}

	Board(const Board& other) : whoseTurn(other.whoseTurn), theBoard(other.theBoard) {}

	bool isLegalMove(const BoardPosition& action) const;
	
	bool checkDir(const BoardPosition& startPosition, const BoardDirection& dir) const;
	
	bool isOppositeColor(const BoardPosition& position, const uint_fast8_t& oppositeColor) const {
		return theBoard.matrixGet(position.x,position.y) == oppositeColor;
	}

private:
	uint_fast8_t whoseTurn;
	BoardVector theBoard;
};

#endif /* end of include guard: BOARD_H__ */