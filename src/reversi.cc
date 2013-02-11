#include "algorithm.h"
#include "board.h"
#include <iostream>

using std::cin;

int main (int argc, char* argv[]) {
	ReversiBoard currentBoard;
	std::string input;
	while(!currentBoard.terminalTest()){
		currentBoard.printBoard();
		cin >> input;
		BoardPosition<> move( input);
		if(currentBoard.tryMakeMove(move)) {
			currentBoard.printBoard();
			currentBoard.makeMove(Algorithm::alphaBetaSearch(currentBoard));
		}
	}
}
