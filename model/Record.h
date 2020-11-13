#pragma once
#include <algorithm>
#include "parsers/StreamObjectParser.h"

struct Record {
	static const int Size = 5;

	int elements[Size];

	Record() = default;

	Record(int* elements) {
		std::copy(elements, elements + Size, this->elements);
	}
};
