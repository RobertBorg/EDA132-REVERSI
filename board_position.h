#ifndef BOARD_POSITION_H__
#define BOARD_POSITION_H__

#include <cstdint>
#include "board_direction.h"

template<uint_fast8_t width = 8, uint_fast8_t height = 8 >
struct BoardPosition {
	uint_fast8_t x;
	uint_fast8_t y;
	BoardPosition (const BoardPosition& other) : x(other.x), y(other.y) {}
	BoardPosition (const uint_fast8_t inX, const uint_fast8_t inY) : x(inX), y(inY) {}

	BoardPosition& add(const BoardDirection& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	bool isValid() {
		return x < width && y < height;
	}
};

#endif /* end of include guard: BOARD_POSITION_H_ */