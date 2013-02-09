#ifndef ALGORITHM_H__
#define ALGORITHM_H__

#include <chrono>
#include "board_position.h"
#include "board.h"

typedef BoardPosition<8,8> ReversiPosition;
typedef Board<8,8> ReversiBoard;
using std::chrono::time_point;

class Algorithm {
public:
	static uint_fast32_t numNodesVisited;
	static ReversiPosition alphaBetaSearch(const ReversiBoard& currentBoard);
private:
	static bool checkRuntime() {
		if(++numNodesVisited %5000000 == 0) {
			auto now = std::chrono::system_clock::now();
			double milis = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
			cout << numNodesVisited/(milis/1000) << endl;
			if(milis > 30000){
				terminate = true;
			}
		}
		return terminate;
	}
	static bool terminate;
	static time_point<std::chrono::system_clock> start;
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
