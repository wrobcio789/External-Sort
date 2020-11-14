#pragma once
#include "Record.h"

class RecordByAverageComparator {

public:
	bool operator()(const Record& a, const Record& b) const;

private:
	int _calculateSumOfRecord(const Record& a) const;

};