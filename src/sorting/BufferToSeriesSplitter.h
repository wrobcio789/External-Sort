#pragma once
#include <vector>
#include "../config/Locator.h"
#include "../io/File.h"
#include "ContignousBufferFiller.h"

class BufferToSeriesSplitter
{
private:
	const Config& _config;

	File* _inputFilePtr;
	size_t _totalRecordsCount;

	CharBuffer& _buffer;
	size_t _seriesSize;

	size_t _currentSeriesIndex;
	std::vector<ContignousBufferFiller> _buffers;

	RecordBuffer _createNthRecordBuffer(size_t n);
	ConstrainedFile _createConstrainedFile();

public:
	BufferToSeriesSplitter(size_t recordsCount, CharBuffer& buffer);

	std::vector<ContignousBufferFiller>& splitNext();

	bool hasNext();

	void setNewTape(File* file, size_t seriesSize);


};

