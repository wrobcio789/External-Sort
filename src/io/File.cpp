#include "File.h"
#include "../config/Locator.h"

File::File(std::string filename, OpenMode mode)
	: _fileStream(filename, mode)
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

void File::write(const CharBuffer& record)
{
	_fileStream.write(record.data, record.size);
	//TODO increment write count
}

size_t File::read(CharBuffer& buffer)
{
	_fileStream.read(buffer.data, buffer.maxSize);
	return buffer.size = _fileStream.gcount();
	//TODO: increment reads counter.
}

