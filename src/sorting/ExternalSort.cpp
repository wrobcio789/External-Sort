#include "ExternalSort.h"
#include "../model/Record.h"
#include "../model/RecordComparators.h"
#include "../model/Buffer.h"
#include "../io/File.h"


ExternalSort::ExternalSort()
	: _config(Locator::get()) {}

void ExternalSort::_firstStageSort()
{
	const size_t mainBufferSize = (_config.pageSize * _config.bufferCount/sizeof(Record)) * sizeof(Record);
	char* mainBufferPtr = new char[mainBufferSize];
	CharBuffer mainBuffer = CharBuffer(mainBufferPtr, mainBufferSize);

	File inputTape(_config.inputFilename, File::OpenMode::READ);
	File outputTape(_config.outputFilename, File::OpenMode::WRITE);
	
	size_t readBytesCount;
	do {
		readBytesCount = inputTape.read(mainBuffer);
		RecordBuffer mainBufferAsRecordsBuffer = mainBuffer.cast<Record>();

		std::sort(mainBufferAsRecordsBuffer.data, mainBufferAsRecordsBuffer.data + mainBufferAsRecordsBuffer.size, RecordByAverageComparator());
		outputTape.write(mainBuffer);
	} while (readBytesCount == mainBuffer.maxSize);
}


void ExternalSort::Sort()
{
	_firstStageSort();
}
