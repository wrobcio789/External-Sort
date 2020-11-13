#pragma once
#include "Record.h"

class RecordByAverageComparator {

public:
	bool operator()(const Record& a, const Record& b) const;

private:
	double _calculateAverageOfRecord(const Record& a) const;

};
