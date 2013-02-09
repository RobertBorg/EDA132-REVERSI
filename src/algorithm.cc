#include "algorithm.h"
#include <limits>
#include <algorithm> // for std::min and std::max

using std::numeric_limits;
using std::min;
using std::max;

uint_fast32_t Algorithm::numNodesVisited = 0;
time_point<std::chrono::system_clock> Algorithm::start;
bool Algorithm::terminate;

ReversiPosition Algorithm::alphaBetaSearch(const ReversiBoard& currentBoard){
	terminate = false;
	start = std::chrono::system_clock::now();
	return initMaxValue(currentBoard,numeric_limits<uint_fast16_t>::min(),numeric_limits<uint_fast16_t>::max());
}

ReversiPosition Algorithm::initMaxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta) {
	ReversiPosition action;
	if(currentBoard.terminalTest(action)){
		return action;
	}

	uint_fast16_t v = numeric_limits<uint_fast16_t>::min();
	ReversiPosition bestMove = action;
	do {
		
		ReversiBoard nextBoard = currentBoard;
		uint_fast16_t minTest = minValue(nextBoard, alpha, beta);
		if(minTest > v){
			v = minTest;
			bestMove = action;
		}
		alpha = max(alpha, v);			
		currentBoard.getNextPossibleMove(action);
	}while (action.isValid());
	return bestMove;
}

uint_fast16_t Algorithm::maxValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta) {
	ReversiPosition action;
	if(currentBoard.terminalTest(action)){
		return currentBoard.utility();
	}
	uint_fast16_t v = numeric_limits<uint_fast16_t>::min();
	if(checkRuntime()) {
		return currentBoard.utility();
	}
	do {
		{
			ReversiBoard nextBoard = currentBoard;
			v = max(v, minValue(result(nextBoard,action), alpha, beta));
		}
		if(v>=beta){
			return v;
		}
		alpha = max(alpha, v);			
		currentBoard.getNextPossibleMove(action);
	}while (action.isValid());
	return v;
}

uint_fast16_t Algorithm::minValue(const ReversiBoard& currentBoard, uint_fast16_t alpha, uint_fast16_t beta) {
	ReversiPosition action;
	if(currentBoard.terminalTest(action)){
		return currentBoard.utility();
	}
	uint_fast16_t v = numeric_limits<uint_fast16_t>::max();
	if(checkRuntime()) {
		return currentBoard.utility();
	}
	do {
		{
			ReversiBoard nextBoard = currentBoard;
			v = min(v, maxValue(result(nextBoard,action), alpha, beta));
		}
		if(v<=alpha){
			return v;
		}
		beta = min(beta, v);
		currentBoard.getNextPossibleMove(action);

	} while (action.isValid());
	return v;
}
