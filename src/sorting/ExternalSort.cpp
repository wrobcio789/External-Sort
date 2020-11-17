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
	size_t readBytesCount;
	do {
		readBytesCount = inputTape->read(buffer);
		totalReadBytes += readBytesCount;
		RecordBuffer bufferAsRecordsBuffer = buffer.cast<Record>();

		std::sort(bufferAsRecordsBuffer.data, bufferAsRecordsBuffer.data + bufferAsRecordsBuffer.size, RecordByAverageLessComparator());
		outputTape->write(buffer);
	} while (readBytesCount == buffer.maxSize);

	return totalReadBytes / sizeof(Record);
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
		while (bufferToSeriesSplitter.hasNext()) {
			std::vector<ContignousBufferFiller>& splitBuffers = bufferToSeriesSplitter.splitNext();
			std::make_heap(splitBuffers.begin(), splitBuffers.end());
			while (!splitBuffers.empty()) {
				ContignousBufferFiller singleBuffer = splitBuffers.front();
				std::pop_heap(splitBuffers.begin(), splitBuffers.end());
				splitBuffers.pop_back();

				outputBuffer.add(singleBuffer.pop());
				if (outputBuffer.isFull()) {
					tapeManager.getOperationalOutput()->write(outputBuffer.cast<char>());
					outputBuffer.size = 0;
				}

				if (singleBuffer.hasNext()) {
					splitBuffers.push_back(singleBuffer);
					std::push_heap(splitBuffers.begin(), splitBuffers.end());
				}
			}
		}
		if (!outputBuffer.isEmpty()) {
			tapeManager.getOperationalOutput()->write(outputBuffer.cast<char>());
			outputBuffer.size = 0;
		}
		//break;
		seriesSizeInRecords *= mergingBuffersCount;
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

