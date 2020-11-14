#pragma once
#include <string>
#include <memory>
#include "../model/Record.h"
#include "../io/printers/SingleRecordPrinter.h"

class Locator {

private:
	Locator() {};

public:
	static Locator& get() {
		static Locator instance;
		return instance;
	}
	
	size_t pageSize = 0;
	size_t bufferCount = 0;

	std::string inputFilename;
	std::string outputFilename;
	
	std::string prettyInputFilename;
	std::string prettyOutputFilename;

	std::unique_ptr<SingleRecordPrinter> recordPrettyPrinterPtr;


	Locator(const Locator&) = delete;
	void operator=(const Locator&) = delete;
};