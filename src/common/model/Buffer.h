#pragma once
#include <cassert>
#include "Record.h"

template<typename T>
class Buffer {

public:
	T* data;
	size_t size;
	size_t maxSize;

	Buffer(T* data = nullptr, size_t maxSize = 0, size_t size = -1)
		: data(data), maxSize(maxSize), size(size == -1 ? maxSize : size) {}

	template<typename Dst>
	Buffer<Dst> cast() {
		return Buffer<Dst>(
			reinterpret_cast<Dst*>(data),
			maxSize * sizeof(T) / sizeof(Dst),
			size * sizeof(T) / sizeof(Dst)
			);
	}

	void add(T value) {
		assert(size < maxSize);

		data[size++] = value;
	}

	bool isFull() {
		assert(size <= maxSize);

		return size == maxSize;
	}

	bool isEmpty() {
		return size == 0;
	}
};

typedef Buffer<Record> RecordBuffer;
typedef Buffer<char> CharBuffer;