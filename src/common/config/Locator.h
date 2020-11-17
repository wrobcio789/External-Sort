#pragma once
#include <string>
#include <memory>
#include "../model/Record.h"
#include "../io/printers/SingleRecordPrinter.h"
#include "../Subprogram.h"

class Config {

public:
	//Common:
	std::string outputFilename;

	//Generator: 
	size_t recordsCount = 0;

	//UserInput: (empty)

	//Sorting:
	bool shouldPrettyPrint = false;
	bool isInteractive = false;
	size_t pageSize = 0;
	size_t bufferCount = 0;
	std::string inputFilename;
	std::string prettyFileSuffix;
	std::string tmpFileSuffix;
	std::unique_ptr<SingleRecordPrinter> recordPrettyPrinterPtr;
};

class Statistics {

private:
	size_t _pagesWritten = 0;
	size_t _pagesRead = 0;
	size_t _sortPhases = 0;

public:
	void registerRead() {
		_pagesRead++;
	}

	void registerWrite() {
		_pagesWritten++;
	}

	void registerNextSortPhase() {
		_sortPhases++;
	}

	void print(std::ostream& stream) {
		stream << "STATISTICS\n"
			<< "Sort phases: " << _sortPhases << "\n"
			<< "Pages written: " << _pagesWritten << "\n"
			<< "Pages read: " << _pagesRead << "\n"
			<< "Total disk operations: " << _pagesWritten + _pagesRead << std::endl;
	}
};

class Locator {

private:
	Locator() {};


public:
	static Locator& get() {
		static Locator instance;
		return instance;
	}

	Config config;
	Statistics statistics;
	std::unique_ptr<Subprogram> program;

	Locator(const Locator&) = delete;
	void operator=(const Locator&) = delete;
};
