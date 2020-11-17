#include "ContignousBufferFiller.h"
#include "../common/model/RecordComparators.h"
#include <cassert>

ContignousBufferFiller::ContignousBufferFiller(RecordBuffer buffer, ConstrainedFile file)
	: _buffer(buffer), _file(file), _elementIndex(0) {
	_readData();
}

Record ContignousBufferFiller::pop()
{
	assert(hasNext());
	
	Record result = _buffer.data[_elementIndex];
	_updatePositions();
	return result;
}

Record ContignousBufferFiller::peek() const {
	assert(hasNext());

	return _buffer.data[_elementIndex];
}

bool ContignousBufferFiller::hasNext() const {
	if (_elementIndex >= _buffer.size)
		return !_file.isEverythingRead();
	return true;
}

bool ContignousBufferFiller::operator<(const ContignousBufferFiller& other)
{
	static RecordByAverageGreaterComparator recordComparator = RecordByAverageGreaterComparator();

	assert(hasNext() && other.hasNext());
	return recordComparator(peek(), other.peek());
	
}

void ContignousBufferFiller::_updatePositions() {
	_elementIndex++;
	if (_elementIndex >= _buffer.size && !_file.isEverythingRead()) {
		_readData();
	}
}

void ContignousBufferFiller::_readData() {
	CharBuffer bufferAsCharBuffer = _buffer.cast<char>();
	_file.read(bufferAsCharBuffer);
	_buffer = bufferAsCharBuffer.cast<Record>();
	_elementIndex = 0;
}

