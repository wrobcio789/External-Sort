#pragma once
#include "Record.h"

typedef Buffer<Record> RecordBuffer;
typedef Buffer<char> CharBuffer;

template<typename T>
class Buffer {

public:
	T* data;
	size_t size;
	size_t maxSize;

	Buffer(T* data, size_t maxCount, size_t currentCount = maxCount)
		: data(data), currentCount(currentCount), maxSize(maxCount) {}

	template<typename Dst>
	Buffer<Dst> cast() {
		const int factor = sizeof(T) / sizeof(Dst);
		return Buffer<Dst>(
			reinterpret_cast<Dst*>(T),
			maxSize * factor
			currenCount * factor,
			);
	}
};