#include "algorithm.h"
#include "board.h"

int main (int argc, char* argv[]) {
	ReversiBoard currentBoard;
	currentBoard.printBoard();
	currentBoard.makeMove(Algorithm::alphaBetaSearch(currentBoard));
	currentBoard.printBoard();
}
