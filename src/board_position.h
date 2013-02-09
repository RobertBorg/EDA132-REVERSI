#ifndef BOARD_POSITION_H__
#define BOARD_POSITION_H__

#include <cstdint>
#include <iostream>
#include "board_direction.h"

using std::cout;
using std::endl;

template<uint_fast8_t width = 8, uint_fast8_t height = 8 >
struct BoardPosition {
	uint_fast8_t x;
	uint_fast8_t y;
	BoardPosition () :x(0), y(0) {}
	BoardPosition (const BoardPosition& other) : x(other.x), y(other.y) {}
	BoardPosition (const uint_fast8_t inX, const uint_fast8_t inY) : x(inX), y(inY) {}

	BoardPosition& add(const BoardDirection& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	BoardPosition& operator++() {
		if(++x == width){
			x = 0;
			++y;
		}
		return *this;
	}

	bool isValid() const {
		return x < width && y < height;
	}

	void print() const {
		cout << static_cast<char>('a' + x) << y+1 << endl;
	}
};

#endif /* end of include guard: BOARD_POSITION_H_ */
