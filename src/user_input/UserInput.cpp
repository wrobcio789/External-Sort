#include "UserInput.h"
#include "../common/model/Buffer.h"
#include "../common/io/BufferedFileWriter.h"
#include <iostream>

UserInput::UserInput(const ArgsParser& args)
	: _config(Locator::get().config) {
	if (!args.isArgumentSpecified("output"))
		throw ArgumentUnspecified("output");

	_config.outputFilename = args.getValue("output").asString();
}

void UserInput::run() {
	size_t recordsNumber;

	std::cout << "How many records are going to be entered: ";
	std::cin >> recordsNumber;

	const size_t bufferSize = 100;
	Record* records = new Record[bufferSize];
	RecordBuffer outputBuffer = RecordBuffer(records, bufferSize, 0);
	File outputFile(_config.outputFilename, File::OpenMode::READ_WRITE);
	BufferedFileWriter<Record> output(&outputFile, outputBuffer);

	for (size_t i = 0; i < recordsNumber; i++) {
		Record record;
		for (int j = 0; j < Record::Size; j++) {
			std::cout << "[" << j << "]: ";
			std::cin >> record.elements[j];
		}
		output.write(record);
	}

	output.flush();

	delete[] records;
}
