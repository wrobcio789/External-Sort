#include "RecordComparators.h"

bool RecordByAverageComparator::operator()(const Record& a, const Record& b) const {
	return _calculateSumOfRecord(a) < _calculateSumOfRecord(b);
}

int RecordByAverageComparator::_calculateSumOfRecord(const Record& record) const {
	int sum = 0;
	for (const int element : record.elements) {
		sum += element;
	}
	return sum;
}
