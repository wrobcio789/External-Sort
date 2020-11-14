#pragma once
#include "Record.h"

template<typename T>
class Buffer {

public:
	T* data;
	size_t size;
	size_t maxSize;

	Buffer(T* data, size_t maxSize, size_t size = -1)
		: data(data), maxSize(maxSize), size(size == -1 ? maxSize : size) {}

	template<typename Dst>
	Buffer<Dst> cast() {
		return Buffer<Dst>(
			reinterpret_cast<Dst*>(data),
			maxSize * sizeof(T) / sizeof(Dst),
			size * sizeof(T) / sizeof(Dst)
			);
	}
};

typedef Buffer<Record> RecordBuffer;
typedef Buffer<char> CharBuffer;