#pragma once
#include <fstream>
#include "SingleRecordPrinter.h"

class PrettyOutput
{
public:
	static void print(const std::string& filename);

private:
	static void print(const SingleRecordPrinter& recordPrinter, std::ifstream& input, std::ofstream& output);
};

