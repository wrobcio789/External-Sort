#pragma once
#include <iostream>

template<typename T>
class StreamObjectParser {

public:
	virtual T read(std::istream & input) const = 0;
	virtual void write(std::ostream & output, const T & object) const = 0;
};
