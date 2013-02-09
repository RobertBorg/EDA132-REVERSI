#ifndef BIT_VECTOR_H__
#define BIT_VECTOR_H__

#include <cstdint>
#include <cstddef>
#include <cstring>

template <size_t numberOfElements, size_t entryBitSize = 1, size_t numberOfElementsPerRow = 1>
class BitVector {
private: 
	uint_fast8_t mem[((entryBitSize * numberOfElements) + (sizeof(uint_fast8_t) * 8) - 1)/(sizeof(uint_fast8_t)*8)];
public:
	BitVector() {
		memset(mem,0,((entryBitSize * numberOfElements) + (sizeof(uint_fast8_t) * 8) - 1)/(sizeof(uint_fast8_t)*8));
	}
	uint_fast8_t get(const size_t index) const {
		const uint_fast8_t bitIndex = index*entryBitSize;
		const uint_fast8_t overflow = bitIndex % (sizeof(uint_fast8_t) * 8);
		const uint_fast8_t byteIndex = bitIndex / (sizeof(uint_fast8_t) * 8);
		return (*(mem + byteIndex) >> overflow) & ((1 << entryBitSize)-1); //TODO: use bitmask lookup table.
	}

	uint_fast8_t matrixGet(const size_t x, const size_t y) const {
		return get(y * numberOfElementsPerRow + x);
	}

	void put(const size_t index, const uint_fast8_t value) {
		const uint_fast8_t bitIndex = index*entryBitSize;
		const uint_fast8_t overflow = bitIndex % (sizeof(uint_fast8_t) * 8);
		const uint_fast8_t byteIndex = bitIndex / (sizeof(uint_fast8_t) * 8);
		const uint_fast8_t negBitmask = ~(((1 << entryBitSize) -1) << overflow);
		*(mem + byteIndex) = (*(mem + byteIndex) & negBitmask) | (value << overflow); //TODO optimize firther
	}

	void matrixPut(const size_t x, const size_t y, const uint_fast8_t value) {
		put(y * numberOfElementsPerRow + x,value);
	}
};
#endif /* end of include guard: BIT_VECTOR_H__ */
