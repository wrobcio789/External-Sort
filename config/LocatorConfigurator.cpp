#include "LocatorConfigurator.h"

void LocatorConfigurator::configure(int argsCount, char* args[]) {
	Locator& locator = Locator::get();

	locator.bufferCount = 1000;
	locator.pageSize = 4096;
	locator.inputFilename = "input.bin";
	locator.outputFilename = "output.bin";
	locator.recordParserPtr = std::make_unique<StreamRecordParser>();
}