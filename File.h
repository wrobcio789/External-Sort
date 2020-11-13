#pragma once
#include <iostream>
#include <fstream>
#include "model/Record.h"
#include "config/Locator.h"
#include "model/parsers/StreamRecordParser.h"
#include "model/Buffer.h"

class File
{
private:
	std::fstream _fileStream;

public:
	File(std::string filename);
	~File();

	void write(const CharBuffer& buffer);

	int read(CharBuffer& buffer);
};

