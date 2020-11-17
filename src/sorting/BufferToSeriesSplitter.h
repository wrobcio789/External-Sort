#pragma once
#include <vector>
#include "ContignousBufferFiller.h"
#include "../common/config/Locator.h"
#include "../common/io/File.h"
#include "../common/io/ConstrainedFile.h"

class BufferToSeriesSplitter
{
private:
	const Config& _config;

	File* _inputFilePtr = nullptr;
	size_t _totalRecordsCount;

	CharBuffer& _buffer;
	size_t _seriesSize = 0;

	size_t _currentSeriesIndex = 0;
	std::vector<ContignousBufferFiller> _buffers;

	RecordBuffer _createNthRecordBuffer(size_t n);
	ConstrainedFile _createConstrainedFile();

public:
	BufferToSeriesSplitter(size_t recordsCount, CharBuffer& buffer);

	std::vector<ContignousBufferFiller>& splitNext();

	bool hasNext();

	void setNewTape(File* file, size_t seriesSize);


};

