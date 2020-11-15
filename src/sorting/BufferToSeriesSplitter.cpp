#include "BufferToSeriesSplitter.h"
#include <cassert>

BufferToSeriesSplitter::BufferToSeriesSplitter(size_t recordsCount, CharBuffer& buffer)
	:	_totalRecordsCount(recordsCount),
		_buffer(buffer),
		_config(Locator::get())
{
	_buffers.reserve(_config.bufferCount - 1);
}

std::vector<ContignousBufferFiller>& BufferToSeriesSplitter::splitNext()
{
	assert(hasNext() && _inputFilePtr != nullptr);

	_buffers.resize(0);
	size_t bufferIndex = 0;
	while (hasNext() && bufferIndex < _config.bufferCount - 1) {
		_buffers.emplace_back(_createNthRecordBuffer(bufferIndex), _createConstrainedFile());
		bufferIndex++;
		_currentSeriesIndex += _seriesSize * sizeof(Record);
	}
	return _buffers;
}

bool BufferToSeriesSplitter::hasNext()
{
	return _currentSeriesIndex / sizeof(Record) < _totalRecordsCount;
}

void BufferToSeriesSplitter::setNewTape(File* file, size_t seriesSize)
{
	_currentSeriesIndex = 0;
	_inputFilePtr = file;
	_seriesSize = seriesSize;
}

RecordBuffer BufferToSeriesSplitter::_createNthRecordBuffer(size_t n) {
	return CharBuffer(_buffer.data + n * _config.pageSize, _config.pageSize).cast<Record>();
}

ConstrainedFile BufferToSeriesSplitter::_createConstrainedFile() {
	return ConstrainedFile(_inputFilePtr, _currentSeriesIndex, _currentSeriesIndex + _seriesSize * sizeof(Record));
}
