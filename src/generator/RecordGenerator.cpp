#include "RecordGenerator.h"
#include <stdlib.h>
#include <ctime>
#include "../common/model/Record.h"
#include "../common/model/Buffer.h"
#include "../common/config/Locator.h"
#include "../common/io/File.h"
#include "../common/io/BufferedFileWriter.h"

RecordGenerator::RecordGenerator(const ArgsParser& args)
	:	_config(Locator::get().config)
{
	if (!args.isArgumentSpecified("output"))
		throw ArgumentUnspecified("output");
	if (!args.isArgumentSpecified("n"))
		throw ArgumentUnspecified("n");


	_config.outputFilename = args.getValue("output").asString();
	_config.recordsCount = args.getValue("n").asLongLong();
}

void RecordGenerator::run() {
	const size_t bufferSize = 10000;
	Record* records = new Record[bufferSize];

	RecordBuffer outputBuffer = RecordBuffer(records, bufferSize, 0);
	File outputFile(_config.outputFilename, File::OpenMode::READ_WRITE);
	BufferedFileWriter<Record> output(&outputFile, outputBuffer);

	srand(time(0));

	for (size_t i = 0; i < _config.recordsCount; i++) {
		Record record;
		for (auto& val : record.elements)
			val = rand();
		output.write(record);
	}
	output.flush();

	delete[] records;
}
