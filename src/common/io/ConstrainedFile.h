#pragma once
#include "File.h"

class ConstrainedFile
{
private:
	File* _filePtr;
	size_t _begin;
	size_t _end;

public:

	ConstrainedFile() = default;

	ConstrainedFile(File* file, size_t begin, size_t end);

	bool isEverythingRead() const;

	size_t read(CharBuffer& buffer);

};

