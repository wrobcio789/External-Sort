#include "StreamRecordParser.h"

Record StreamRecordParser::read(std::istream & input) const
{
	int T[Record::Size];
	for (int i = 0; i < Record::Size; i++) {
		input >> T[i];
	}
	return Record(T);
}

void StreamRecordParser::write(std::ostream & output, const Record& record) const
{
	for (int i = 0; i < Record::Size; i++) {
		output << record.elements[i] <<' ';
	}
}
