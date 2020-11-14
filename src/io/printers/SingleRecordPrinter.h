#pragma once
#include <ostream>
#include <istream>

class SingleRecordPrinter
{
public:
	virtual void initStreams(std::istream& input, std::ostream& output) const {}

	virtual void print(std::istream& input, std::ostream& output) const = 0;
};

