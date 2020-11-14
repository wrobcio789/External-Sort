#pragma once
#include <fstream>
#include "SingleRecordPrinter.h"

class PrettyOutput
{
public:
	static void print();

private:
	static void _printUnchecked(const SingleRecordPrinter& recordPrinter, std::ifstream& input, std::ofstream& output);
};

