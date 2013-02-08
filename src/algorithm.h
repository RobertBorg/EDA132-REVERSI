#ifndef ALGORITHM_H__
#define ALGORITHM_H__

#include "board_position.h"
#include "board.h"

typedef BoardPosition<8,8> ReversiPosition;
typedef Board<8,8> ReversiBoard;

class Algorithm {
public:
	static uint_fast32_t numNodesVisited;
	static ReversiPosition alphaBetaSearch(const ReversiBoard& currentBoard);
private:
	static uint_fast16_t maxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta);
	static uint_fast16_t minValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta);
	static ReversiPosition initMaxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta);

	static ReversiBoard result(const ReversiBoard& currentBoard, const ReversiPosition& action){
		ReversiBoard rtn = currentBoard;
		rtn.makeMove(action);
		return rtn;
	}
	static ReversiBoard& result(ReversiBoard& currentBoard, const ReversiPosition& action){
		currentBoard.makeMove(action);
		return currentBoard;
	}
};

#endif /* end of include guard: ALGORITHM_H__ */
