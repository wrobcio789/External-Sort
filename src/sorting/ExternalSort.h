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

	size_t _firstStageSort(CharBuffer& buffer, TapeManager& tapeManager) const;
	void _createSingleSeries(File* inputTape, File* outputTape, CharBuffer& buffer) const;

	void _secondStageSort(CharBuffer& buffer, size_t recordsCount, TapeManager& tapeManager) const;
	void _mergeSeries(BufferToSeriesSplitter & splitter, TapeManager& tapeManager, BufferedFileWriter<Record>& outputBuffer, size_t seriesSizeInRecords) const;
	void _pickNextToOutput(std::vector<ContignousBufferFiller>& splitBuffers, TapeManager& tapeManager, BufferedFileWriter<Record>& recordWriter) const;

public:
	ExternalSort();

	void Sort();
};

