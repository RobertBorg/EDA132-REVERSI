#ifndef BOARD_H__
#define BOARD_H__

#include <cstddef>
#include <iostream>
#include "board_vector.h"
#include "board_position.h"
#include "board_direction.h"
#include "board_rectangle.h"

using std::cout;
using std::endl;

template<uint_fast8_t boardWidth = 8, uint_fast8_t boardHeight = 8 >
class Board {
public:
	typedef BoardPosition<boardWidth,boardHeight> BoardPos;
	static const uint_fast8_t Light = 0b01;
	static const uint_fast8_t Dark = 0b11;

	Board() : whoseTurn(Dark) {
		theBoard.matrixPut(3,3,Dark);
		theBoard.matrixPut(4,3,Light);
		theBoard.matrixPut(3,4,Light);
		theBoard.matrixPut(4,4,Dark);
	}

	Board(const Board& other) : whoseTurn(other.whoseTurn), theBoard(other.theBoard) {}

	bool isLegalMove(const BoardPos& action, BoardDirection& dir) const {
		if(!(action.isValid() && theBoard.matrixGet(action.x,action.y) == 0)) {
			return false;
		}

		for (; dir != INVALID_DIRECTION; ++dir) {
			if(checkDir(action, dir)){
				return true;
			}
		}
		return false;
	}

	bool isLegalMove(const BoardPos& action) const {
		BoardDirection dir;
		return isLegalMove(action,dir);
	}
	
	bool checkDir(const BoardPos& startPosition, const BoardDirection& dir) const {
		const uint_fast8_t oppositeColor = whoseTurn ^ 0b10;
		BoardPos currentPosition(startPosition);

		currentPosition.add(dir);
		if(currentPosition.isValid() && theBoard.matrixGet(currentPosition.x,currentPosition.y) == oppositeColor) {
			do {
				currentPosition.add(dir);
				uint_fast8_t tile = theBoard.matrixGet(currentPosition.x,currentPosition.y);
				if(tile == 0){
					return false;
				}
				if( tile == whoseTurn){
					return true;
				}
				
			} while (currentPosition.isValid());
		}
		return false;
	}
	
	bool isOppositeColor(const BoardPos& position, const uint_fast8_t& oppositeColor) const {
		return theBoard.matrixGet(position.x,position.y) == oppositeColor;
	}

	bool terminalTest(BoardPos& action, const BoardRectangle& rect) const{
		getNextPossibleMove(action,rect);
		return !action.isValid();
	}

	bool terminalTest() const{
		BoardPos action;
		BoardRectangle rect;

		rect.first.x = 0;
		rect.first.y = 0;
		rect.second.x = 8;
		rect.second.y = 8;

		getNextPossibleMove(action,rect);
		return !action.isValid();
	}

	void getNextPossibleMove(BoardPos& action, const BoardRectangle& rect) const{
		for(;action.y != rect.second.y ;++action.y) {
			for(;action.x != rect.second.y ;++action.x) {
				if(isLegalMove(action)){
					return;
				}
			}
			action.x = rect.first.x;
		}
		action.y = boardHeight;
	}

	void flipTiles(const BoardPos& action, const BoardDirection& dir){
		BoardPos pos = action;
		const uint_fast8_t otherColor = whoseTurn ^ 0b10;
		while(1) {
			pos.add(dir);
			uint_fast8_t& tile = theBoard.matrixGet(pos.x, pos.y);
			if(tile == otherColor){
				tile = whoseTurn;
			} else {
				break;
			}
		}
	}

	uint_fast16_t utility() const {
		BoardPos pos;
		uint_fast16_t points(0);
		if( whoseTurn == Dark){
			for(size_t i = 0; i != 64;++i) {
				switch (theBoard.get(i)){
					case Dark:
						points += 2;
						break;
					case Light:
						break;
					default:
						++points;
						break;						
				}
			}
		} else {
			for(size_t i = 0; i != 64;++i) {
				switch (theBoard.get(i)){
					case Dark:
						break;
					case Light:
						points += 2;
						break;
					default:
						++points;
						break;						
				}
			}
		}
		return points;
	}
	void makeMove(const BoardPos& action) {
		BoardDirection dir;
		while(isLegalMove(action, dir)){
			flipTiles(action, dir);
			++dir;
		}
		theBoard.matrixPut(action.x,action.y,whoseTurn);
		whoseTurn ^= 0b10;
	}

	void makeMoveWithRectangleExpansion(const BoardPos& action, BoardRectangle& currentRangeOfPossibleMoves) {
		makeMove(action);
		if(action.x == currentRangeOfPossibleMoves.first.x) {
			if(--currentRangeOfPossibleMoves.first.x > boardWidth){
				++currentRangeOfPossibleMoves.first.x;
			}
		}
		if(action.x == currentRangeOfPossibleMoves.second.x -1) {
			if(++currentRangeOfPossibleMoves.second.x > boardWidth) {
				--currentRangeOfPossibleMoves.second.x;
			}
		}
		if(action.y == currentRangeOfPossibleMoves.first.y) {
			if(--currentRangeOfPossibleMoves.first.y > boardHeight) {
				++currentRangeOfPossibleMoves.first.y;
			}
		}
		if(action.y == currentRangeOfPossibleMoves.second.y - 1) {
			if(++currentRangeOfPossibleMoves.second.y > boardHeight){
				--currentRangeOfPossibleMoves.second.y;
			}
		}
	}

	void printBoard() const {
		BoardPos pos;
		cout << " abcdefgh" << endl;
		for(;pos.y != boardHeight;++pos.y) {
			cout << static_cast<int>(pos.y+1);
			for(;pos.x != boardWidth;++pos.x) {
				cout << getColor(theBoard.matrixGet(pos.x,pos.y));
			}
			cout << endl;
			pos.x = 0;
		}
	}

	static const char getColor(uint_fast8_t color) {
		switch(color){
			case Light:
				return 'L';
				break;
			case Dark:
				return 'D';
				break;
			default:
				return '-';
				break;
		}
	}

	bool tryMakeMove(const BoardPos& action) {
		if(action.isValid() && isLegalMove(action)) {
			makeMove(action);
			return true;
		}
		return false;
	}

private:
	uint_fast8_t whoseTurn;
	BoardVector<boardWidth * boardHeight, boardWidth> theBoard;
};

#endif /* end of include guard: BOARD_H__ */
