#ifndef BOARD_VECTOR_H__
#define BOARD_VECTOR_H_

#include <vector>
#include <cstdint>
#include <cstring>


using std::vector;

template<size_t numElements, size_t numElementsPerRow>
class BoardVector {
public:
	BoardVector() {
		memset(mem, 0, numElements);
	}
	BoardVector(const BoardVector& other ) {
		memcpy(mem, other.mem, sizeof(uint_fast8_t) * numElements);
	}

	uint_fast8_t matrixGet(const size_t x, const size_t y) const {
		return get(numElementsPerRow * y + x);
	}

	const uint_fast8_t get(const size_t index) const {
		return mem[index];
	}

	void matrixPut(const size_t x, const size_t y, uint_fast8_t value ) {
		put(numElementsPerRow * y + x, value);
	}

	void put(const size_t index, const uint_fast8_t value) {
		mem[index] = value;
	}

private:
	uint_fast8_t mem[numElements];
};

#endif /* end of include guard: BOARD_VECTOR_H__ */