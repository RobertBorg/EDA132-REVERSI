#ifndef BOARD_DIRECTION_H__
#define BOARD_DIRECTION_H__

#include <cstdint>


enum direction_t {
					UP = 0,
					UP_RIGHT,
					RIGHT,
					DOWN_RIGHT,
					DOWN,
					DOWN_LEFT,
					LEFT,
					UP_LEFT,
					INVALID_DIRECTION
				};
				
direction_t& operator++(direction_t& dir);
class BoardDirection;
bool operator!=(BoardDirection& lhs, int rhs);

class BoardDirection {
public:
	direction_t dir;
	int_fast8_t x;
	int_fast8_t y;
	BoardDirection() : dir(UP), x(0), y(0) {}
	BoardDirection& operator++() {
		switch(++dir) {
			case UP:
				x=0;
				y=-1;
			break;
			case UP_RIGHT:
				x=1;
				y=-1;
			break;
			case RIGHT:
				x=1;
				y=0;
			break;
			case DOWN_RIGHT:
				x=1;
				y=1;
			break;
			case DOWN:
				x=0;
				y=1;
			break;
			case DOWN_LEFT:
				x=-1;
				y=1;
			break;
			case LEFT:
				x=-1;
				y=0;
			break;
			case UP_LEFT:
				x=-1;
				y=-1;
			break;
			case INVALID_DIRECTION:
				x=0;
				y=0;
			break;
		}
		return *this;
	}
};

#endif /* end of include guard: BOARD_DIRECTION_H__ */
