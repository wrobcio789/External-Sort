#include <iomanip>
#include <string>
#include "FormatedRecordPrinter.h"
#include "../../model/Record.h"

void FormatedRecordPrinter::initStreams(std::istream& input, std::ostream& output) const
{
	for (int i = 0; i < Record::Size; i++)
		output << std::setw(10) << "[" + std::to_string(i) + "]";
	output << std::setw(10) << "sum\n";
}

void FormatedRecordPrinter::print(std::istream& input, std::ostream& output) const
{
	Record record;
	input.read(reinterpret_cast<char*>(&record), sizeof(Record));
	for (int i = 0; i < Record::Size; i++) {
		output << std::setw(10) << record.elements[i];
	}

	output << std::setw(10) << record.sum() << '\n';
}
