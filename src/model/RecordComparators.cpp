#include "RecordComparators.h"

int _calculateSumOfRecord(const Record& record) {
	int sum = 0;
	for (const int element : record.elements) {
		sum += element;
	}
	return sum;
}

bool RecordByAverageLessComparator::operator()(const Record& a, const Record& b) const {
	return _calculateSumOfRecord(a) < _calculateSumOfRecord(b);
}

bool RecordByAverageGreaterComparator::operator()(const Record& a, const Record& b) const
{
	return _calculateSumOfRecord(a) > _calculateSumOfRecord(b);
}
