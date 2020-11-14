#pragma once
#include <iostream>
#include <fstream>
#include "../model/Buffer.h"

class File
{
private:
	std::fstream _fileStream;

public:
	enum OpenMode {
		READ = std::fstream::in | std::fstream::binary,
		WRITE = std::fstream::out | std::fstream::binary,
	};

	File(std::string filename, OpenMode mode);
	~File();

	void write(const CharBuffer& buffer);

	size_t read(CharBuffer& buffer);

};

