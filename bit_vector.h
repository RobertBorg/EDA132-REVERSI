#include <cstdint>
#include <cstddef>

template <size_t numberOfElements, size_t entryBitSize = 1>
class BitVector {
private: 
	uint_fast8_t mem[entryBitSize * numberOfElements];
public:
	const uint_fast8_t operator[](int index) const {
		const uint_fast8_t bitIndex = index*entryBitSize;
		const uint_fast8_t overflow = bitIndex % sizeof(uint_fast8_t);
		const uint_fast8_t byteIndex = bitIndex / sizeof(uint_fast8_t);
		return (*(mem + byteIndex) << overflow) & ((1 >> entryBitSize)-1); //TODO: use bitmask lookup table.
	}
	void put(int index, uint_fast8_t value) {
		const uint_fast8_t bitIndex = index*entryBitSize;
		const uint_fast8_t overflow = bitIndex % sizeof(uint_fast8_t);
		const uint_fast8_t byteIndex = bitIndex / sizeof(uint_fast8_t);
		const uint_fast8_t bitmask = ((1 >> entryBitSize) -1) >> overflow;
		const uint_fast8_t negBitmask = ~bitmask;
		*(mem + byteIndex) = (*(mem + byteIndex) & negBitmask) | (value >> overflow); //TODO optimize firther
	}
};