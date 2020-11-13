#pragma once
#include <string>
#include "../model/Record.h"
#include <memory>

class Locator {
public:
	static Locator& get() {
		return _instance;
	}
	
	unsigned int pageSize;
	unsigned int bufferCount;

	std::string inputFilename;
	std::string outputFilename;

	std::unique_ptr<StreamObjectParser<Record>> recordParserPtr;

private:
	static Locator _instance;

	Locator();
};