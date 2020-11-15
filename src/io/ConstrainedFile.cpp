#include <algorithm>
#include <cassert>
#include "ConstrainedFile.h"
#include "../config/Locator.h"


ConstrainedFile::ConstrainedFile(File* file, size_t begin, size_t end)
	: _filePtr(file), _begin(begin), _end(end) {
	assert(end > begin);
}

bool ConstrainedFile::isEverythingRead() const 
{
	return _begin >= _end;
}

size_t ConstrainedFile::read(CharBuffer& buffer)
{
	assert(_filePtr != nullptr);

	size_t readBytes = _filePtr->rangedRead(buffer, _begin, _end);
	if (readBytes < buffer.maxSize)
		_begin = _end;

	_begin += readBytes;
	return readBytes;
}
