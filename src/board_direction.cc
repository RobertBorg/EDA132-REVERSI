#include "board_direction.h"

bool operator!=(BoardDirection& lhs, int rhs) {
	return lhs.dir != rhs;
}
direction_t& operator++(direction_t& dir) {
	dir = static_cast<direction_t>(dir + 1);
	return dir;
}