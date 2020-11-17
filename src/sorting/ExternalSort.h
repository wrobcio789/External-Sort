#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include "ContignousBufferFiller.h"
#include "BufferToSeriesSplitter.h"
#include "TapeManager.h"

class ExternalSort
{
private:
	const Config& _config;

	size_t _firstStageSort(CharBuffer& buffer, TapeManager& tapeManager) const;

	void _secondStageSort(CharBuffer& buffer, size_t recordsCount, TapeManager& tapeManager) const;

	void ExternalSort::_createSingleSeries(File* inputTape, File* outputTape, CharBuffer& buffer) const

	void _mergeSeries(BufferToSeriesSplitter & splitter, TapeManager& tapeManager, RecordBuffer& outputBuffer, size_t seriesSizeInRecords) const;

	void _pickNextToOutput(std::vector<ContignousBufferFiller>& splitBuffers, TapeManager& tapeManager, RecordBuffer& outputBuffer) const;

public:
	ExternalSort();

	void Sort();
};

