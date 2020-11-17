#include "ExternalSort.h"
#include "../common/model/Record.h"
#include "../common/model/RecordComparators.h"
#include "../common/io/File.h"
#include "BufferToSeriesSplitter.h"

ExternalSort::ExternalSort()
	: _config(Locator::get().config) {}

size_t ExternalSort::_firstStageSort(CharBuffer& buffer, TapeManager& tapeManager) const
{
	File* inputTape = tapeManager.getInput();
	File* outputTape = tapeManager.getOperationalOutput();
	
	size_t totalReadBytes = 0;
	do {
		_createSingleSeries(inputTape, outputTape, buffer);
		totalReadBytes += buffer.size;
	} while (buffer.size == buffer.maxSize);

	return totalReadBytes / sizeof(Record);
}

void ExternalSort::_createSingleSeries(File* inputTape, File* outputTape, CharBuffer& buffer) const{
	inputTape->read(buffer);
	RecordBuffer bufferAsRecordsBuffer = buffer.cast<Record>();
	std::sort(bufferAsRecordsBuffer.data, bufferAsRecordsBuffer.data + bufferAsRecordsBuffer.size, RecordByAverageLessComparator());
	outputTape->write(buffer);
}

void ExternalSort::_secondStageSort(CharBuffer& buffer, size_t recordsCount, TapeManager& tapeManager) const {
	const size_t mergingBuffersCount = _config.bufferCount - 1;
	CharBuffer mergingBuffer = CharBuffer(buffer.data, buffer.maxSize - _config.pageSize);

	RecordBuffer outputBuffer = CharBuffer(mergingBuffer.data + mergingBuffer.maxSize, _config.pageSize, 0).cast<Record>();


	size_t seriesSizeInRecords = buffer.cast<Record>().maxSize;
	BufferToSeriesSplitter bufferToSeriesSplitter(recordsCount, mergingBuffer);

	while (seriesSizeInRecords < recordsCount) {
		tapeManager.swap();
		bufferToSeriesSplitter.setNewTape(tapeManager.getOperationalInput(), seriesSizeInRecords);
		BufferedFileWriter<Record> recordWriter(tapeManager.getOperationalOutput(), outputBuffer);

		_mergeSeries(bufferToSeriesSplitter, tapeManager, recordWriter, seriesSizeInRecords);

		recordWriter.flush();
		seriesSizeInRecords *= mergingBuffersCount;
	}
}

void ExternalSort::_mergeSeries(BufferToSeriesSplitter& splitter, TapeManager& tapeManager, BufferedFileWriter<Record>& recordWriter, size_t seriesSizeInRecords) const {
	splitter.setNewTape(tapeManager.getOperationalInput(), seriesSizeInRecords);
	while (splitter.hasNext()) {
		std::vector<ContignousBufferFiller>& splitBuffers = splitter.splitNext();
		std::make_heap(splitBuffers.begin(), splitBuffers.end());
		while (!splitBuffers.empty()) {
			_pickNextToOutput(splitBuffers, tapeManager, recordWriter);
		}
	}
}

void ExternalSort::_pickNextToOutput(std::vector<ContignousBufferFiller>& splitBuffers, TapeManager& tapeManager, BufferedFileWriter<Record>& recordWriter) const {
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
	const size_t mainBufferSize = (_config.pageSize * _config.bufferCount / sizeof(Record)) * sizeof(Record);
	char* mainBufferPtr = new char[mainBufferSize];
	CharBuffer mainBuffer = CharBuffer(mainBufferPtr, mainBufferSize);

	TapeManager tapeManager;
	size_t totalRecordsCount = _firstStageSort(mainBuffer, tapeManager);
	_secondStageSort(mainBuffer, totalRecordsCount, tapeManager);

	delete[] mainBufferPtr;
}

