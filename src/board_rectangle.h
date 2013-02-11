#ifndef BOARD_RECTANGLE_H__
#define BOARD_RECTANGLE_H__

#include <cstdint>
#include "board_position.h"

class BoardRectangle {
public:
	BoardPosition<8,8> first;
	BoardPosition<8,8> second;

	BoardRectangle() : first(2,2), second(6,6) {}
	BoardRectangle(const BoardRectangle& other) : first(other.first) , second(other.second) {}
};

#endif /* end of include guard: BOARD_RECTANGLE_H__ */