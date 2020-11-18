#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include "../config/Locator.h"
#include "../model/Buffer.h"

class CannotOpenFileException : public std::exception {
	const std::string _message;

public:
	CannotOpenFileException(std::string filename) : _message("Cannot open file: " + filename) {}

	const char* what() const override {
		return _message.c_str();
	}
};

class File
{
private:
	std::string _name;
	std::fstream _fileStream;

	Statistics& _statistics;

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

	void flush();
};

