#include "File.h"
#include <algorithm>
#include <cassert>
#include "../config/Locator.h"

int _calculatePages(int size) {
	const int pageSize = Locator::get().config.pageSize;
	return (size + pageSize - 1) / pageSize;
}

File::File(std::string filename, OpenMode mode)
	: _name(filename), _fileStream(filename, mode), _statistics(Locator::get().statistics)
{
	if (!_fileStream.is_open()) {
		throw CannotOpenFileException(filename);
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
	_statistics.registerWrite(_calculatePages(record.size));
}

size_t File::read(CharBuffer& buffer)
{
	_fileStream.read(buffer.data, buffer.maxSize);
	buffer.size = _fileStream.gcount();
	
	_statistics.registerRead(_calculatePages(buffer.size));
	return buffer.size;
}

size_t File::rangedRead(CharBuffer& buffer, size_t begin, size_t end) {
	const size_t readSize = std::min(buffer.maxSize, end - begin);

	_fileStream.clear();
	_fileStream.seekg(begin);
	_fileStream.read(buffer.data, readSize);


	buffer.size = _fileStream.gcount();
	_statistics.registerRead(_calculatePages(buffer.size));

	return buffer.size;
}

void File::reset() {
	_fileStream.clear();
	_fileStream.seekp(std::fstream::beg);
	_fileStream.seekg(std::fstream::beg);
}

void File::flush() {
	_fileStream.flush();
}
