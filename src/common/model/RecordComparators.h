#pragma once
#include "Record.h"

class RecordByAverageLessComparator {

public:
	bool operator()(const Record& a, const Record& b) const;
};

class RecordByAverageGreaterComparator {

public:
	bool operator()(const Record& a, const Record& b) const;
};