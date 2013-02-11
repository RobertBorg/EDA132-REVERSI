#ifndef ALGORITHM_H__
#define ALGORITHM_H__

#include <chrono>
#include <iostream>
#include "board_position.h"
#include "board.h"
#include "board_rectangle.h"

typedef BoardPosition<8,8> ReversiPosition;
typedef Board<8,8> ReversiBoard;
using std::chrono::time_point;

class Algorithm {
public:
	static uint_fast32_t numNodesVisited;
	static ReversiPosition alphaBetaSearch(const ReversiBoard& currentBoard);
private:
	static bool checkRuntime() {
		if(++numNodesVisited %250000 == 0) {
			auto now = std::chrono::system_clock::now();
			double milis = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
			cout << numNodesVisited/(milis/1000) << endl;
			if(milis > 5000){
				terminate = true;
			}
		}
		return terminate;
	}
	static bool terminate;
	static time_point<std::chrono::system_clock> start;
	static uint_fast16_t maxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta, const BoardRectangle& currentRangeOfPossibleMoves);
	static uint_fast16_t minValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta, const BoardRectangle& currentRangeOfPossibleMoves);
	static ReversiPosition initMaxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta, const BoardRectangle& currentRangeOfPossibleMoves);

	static ReversiBoard result(const ReversiBoard& currentBoard, const ReversiPosition& action, const BoardRectangle& currentRangeOfPossibleMoves){
		BoardRectangle rect = currentRangeOfPossibleMoves;
		ReversiBoard rtn = currentBoard;
		rtn.makeMoveWithRectangleExpansion(action,rect);
		return rtn;
	}
	static ReversiBoard& result(ReversiBoard& currentBoard, const ReversiPosition& action, BoardRectangle& currentRangeOfPossibleMoves){
		currentBoard.makeMoveWithRectangleExpansion(action,currentRangeOfPossibleMoves);

		return currentBoard;
	}
};

#endif /* end of include guard: ALGORITHM_H__ */
