#include "ExternalSort.h"
#include "../common/model/Record.h"
#include "../common/model/RecordComparators.h"
#include "../common/io/File.h"
#include "BufferToSeriesSplitter.h"

ExternalSort::ExternalSort()
	: _config(Locator::get().config) {

	const size_t mainBufferSize = (_config.pageSize * _config.bufferCount / sizeof(Record)) * sizeof(Record);
	char* mainBufferPtr = new char[mainBufferSize];

	_mainBuffer = CharBuffer(mainBufferPtr, mainBufferSize);
}

ExternalSort::~ExternalSort(){
	delete[] _mainBuffer.data;
}

size_t ExternalSort::_firstStageSort()
{
	size_t totalReadBytes = 0;
	do {
		_createSingleSeries();
		totalReadBytes += _mainBuffer.size;
	} while (_mainBuffer.size == _mainBuffer.maxSize);

	return totalReadBytes / sizeof(Record);
}

void ExternalSort::_createSingleSeries(){
	_tapeManager.getInput()->read(_mainBuffer);

	RecordBuffer bufferAsRecordsBuffer = _mainBuffer.cast<Record>();
	std::sort(bufferAsRecordsBuffer.data, bufferAsRecordsBuffer.data + bufferAsRecordsBuffer.size, RecordByAverageLessComparator());

	_tapeManager.getOperationalOutput()->write(_mainBuffer);
}

void ExternalSort::_secondStageSort(size_t recordsCount) {
	const size_t mergingBuffersCount = _config.bufferCount - 1;
	CharBuffer mergingBuffer = CharBuffer(_mainBuffer.data, _mainBuffer.maxSize - _config.pageSize);
	RecordBuffer outputBuffer = CharBuffer(mergingBuffer.data + mergingBuffer.maxSize, _config.pageSize, 0).cast<Record>();

	size_t seriesSizeInRecords = _mainBuffer.cast<Record>().maxSize;
	BufferToSeriesSplitter splitter(recordsCount, mergingBuffer);

	while (seriesSizeInRecords < recordsCount) {
		_tapeManager.swap();
		_mergeSeries(splitter, outputBuffer, seriesSizeInRecords);
		seriesSizeInRecords *= mergingBuffersCount;
	}
}

void ExternalSort::_mergeSeries(BufferToSeriesSplitter& splitter, RecordBuffer& outputBuffer, size_t seriesSizeInRecords) {
	splitter.setNewTape(_tapeManager.getOperationalInput(), seriesSizeInRecords);
	BufferedFileWriter<Record> recordWriter(_tapeManager.getOperationalOutput(), outputBuffer);

	while (splitter.hasNext()) {
		std::vector<ContignousBufferFiller>& splitBuffers = splitter.splitNext();
		std::make_heap(splitBuffers.begin(), splitBuffers.end());
		while (!splitBuffers.empty()) {
			_pickNextToOutput(splitBuffers, recordWriter);
		}
	}

	recordWriter.flush();
}

void ExternalSort::_pickNextToOutput(std::vector<ContignousBufferFiller>& splitBuffers, BufferedFileWriter<Record>& recordWriter) {
	ContignousBufferFiller singleBuffer = splitBuffers.front();
	std::pop_heap(splitBuffers.begin(), splitBuffers.end());
	splitBuffers.pop_back();

	recordWriter.write(singleBuffer.pop());

	if (singleBuffer.hasNext()) {
		splitBuffers.push_back(singleBuffer);
		std::push_heap(splitBuffers.begin(), splitBuffers.end());
	}
}

void ExternalSort::Sort()
{
	size_t totalRecordsCount = _firstStageSort();
	_secondStageSort(totalRecordsCount);
}

