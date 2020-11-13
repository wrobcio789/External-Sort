#include "ExternalSort.h"


ExternalSort::ExternalSort()
	: _config(Locator::get()) {}

void ExternalSort::_firstStageSort()
{
	const int mainBufferSize = _config.pageSize * _config.bufferCount;
	char* mainBufferPtr = new char[mainBufferSize];
	CharBuffer mainBuffer = CharBuffer(mainBufferPtr, mainBufferSize);

	File inputTape(_config.inputFilename);
	File outputTape(_config.outputFilename);
	
	int readBytesCount;
	do {
		readBytesCount = inputTape.read(mainBuffer);
		RecordBuffer mainBufferAsRecordsBuffer = mainBuffer.cast();

		std::sort(mainBufferAsRecordsBuffer.data, mainBufferAsRecordsBuffer.data + mainBufferAsRecordsBuffer.size);
		outputTape.write(mainBuffer);
	} while (readBytesCount == mainBuffer.size);
}


void ExternalSort::Sort()
{
	_firstStageSort();
}
