#pragma once
#include <algorithm>
#include <numeric>

struct Record {
	static const int Size = 5;

	int elements[Size];

	Record() = default;

	Record(int* elements) {
		std::copy(elements, elements + Size, this->elements);
	}

	int sum() {
		return std::accumulate(elements, elements + Size, 0);
	}
};
