#include "board.h"

bool Board::isLegalMove(const BoardPosition& action) const {
	if(!(action.x < 8 && action.y < 8 && theBoard.matrixGet(action.x,action.y) == 0)) {
		return false;
	}

	for (BoardDirection dir; dir != INVALID_DIRECTION; ++dir) {
		if(checkDir(action, dir)){
			return true;
		}
	}
	return false;
}

bool Board::checkDir(const BoardPosition& startPosition, const BoardDirection& dir) const {
	const uint_fast8_t oppositeColor = whoseTurn ^ 0b01;
	BoardPosition currentPosition(startPosition);

	currentPosition.add(dir);
	if(isOppositeColor(currentPosition, oppositeColor)) {
		do {
			currentPosition.add(dir);
			if(!isOppositeColor(currentPosition, oppositeColor)){
				return true;
			}
		} while (currentPosition.isValid());
	}
	return false;
}