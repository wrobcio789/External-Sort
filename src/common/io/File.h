#pragma once
#include <iostream>
#include <fstream>
#include "../model/Buffer.h"

class File
{
private:
	std::string _name;
	std::fstream _fileStream;

public:
	enum OpenMode {
		READ = std::fstream::in | std::fstream::binary,
		READ_WRITE = std::fstream::in | std::fstream::trunc | std::fstream::out | std::fstream::binary,
	};

	std::string getName() const;

	File(std::string filename, OpenMode mode);
	~File();

	void write(const CharBuffer& buffer);

	size_t read(CharBuffer& buffer);

	size_t rangedRead(CharBuffer& buffer, size_t begin, size_t end);

	void reset();
};
