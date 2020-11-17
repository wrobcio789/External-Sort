#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include "ContignousBufferFiller.h"
#include "BufferToSeriesSplitter.h"
#include "../common/io/BufferedFileWriter.h"
#include "TapeManager.h"

class ExternalSort
{
private:
	const Config& _config;
	CharBuffer _mainBuffer;
	TapeManager _tapeManager;

	size_t _firstStageSort();
	void _createSingleSeries();

	void _secondStageSort(size_t recordsCount);
	void _mergeSeries(BufferToSeriesSplitter& splitter, RecordBuffer& recordWriter, size_t seriesSizeInRecords);
	void _pickNextToOutput(std::vector<ContignousBufferFiller>& splitBuffers,  BufferedFileWriter<Record>& recordWriter);

public:
	ExternalSort();
	~ExternalSort();

	void Sort();
};

