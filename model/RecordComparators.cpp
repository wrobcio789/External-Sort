#include "RecordComparators.h"

bool RecordByAverageComparator::operator()(const Record& a, const Record& b) const {
	return _calculateAverageOfRecord(a) < _calculateAverageOfRecord(b);
}

double RecordByAverageComparator::_calculateAverageOfRecord(const Record& record) const {
	int sum = 0;
	for (const int element : record.elements) {
		sum += element;
	}
	return static_cast<double>(sum)/static_cast<double>(record.Size);
}
