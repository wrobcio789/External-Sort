#include "File.h"
#include <algorithm>
#include <cassert>
#include "../config/Locator.h"

bool _isExacltyOneDiskPageRead(size_t begin, size_t readSize) {
	size_t diskPageSize = Locator::get().pageSize;

	size_t beginDiskPageIndex = begin / diskPageSize;
	size_t endDiskPageIndex = (begin + readSize - 1) / diskPageSize;
	return beginDiskPageIndex == endDiskPageIndex;
}

File::File(std::string filename, OpenMode mode)
	: _name(filename), _fileStream(filename, mode)
{
	if (!_fileStream.is_open()) {
		std::cerr << "File " + filename + " cannot be opened" << std::endl;
		exit(1);
	}
}

File::~File()
{
	_fileStream.close();
}

std::string File::getName() const{
	return _name;
}

void File::write(const CharBuffer& record)
{
	_fileStream.write(record.data, record.size);
	//TODO increment write counter
}

size_t File::read(CharBuffer& buffer)
{
	_fileStream.read(buffer.data, buffer.maxSize);
	return buffer.size = _fileStream.gcount();
	//TODO: increment reads counter.
}

size_t File::rangedRead(CharBuffer& buffer, size_t begin, size_t end) {
	const size_t readSize = std::min(buffer.maxSize, end - begin);
	assert(_isExacltyOneDiskPageRead(begin, readSize));

	_fileStream.clear();
	_fileStream.seekg(begin);

	_fileStream.read(buffer.data, readSize);
	return buffer.size = _fileStream.gcount();
	//TODO: increment reads counter.
}

void File::reset() {
	_fileStream.clear();
	_fileStream.seekp(std::fstream::beg);
	_fileStream.seekg(std::fstream::beg);
}