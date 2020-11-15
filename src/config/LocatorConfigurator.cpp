#include "LocatorConfigurator.h"

void LocatorConfigurator::configure(int argsCount, char* args[]) {
	Locator& locator = Locator::get();

	locator.bufferCount = 100;
	locator.pageSize = 4096;
	locator.inputFilename = "./data/input1000000.bin";
	locator.outputFilename = "./data/output1000000.bin";

	locator.prettyInputFilename = "./data/pretty_input1000000.txt";
	locator.prettyOutputFilename = "./data/pretty_output1000000.txt";

	locator.tmpFileSuffix = ".tmp";
	locator.recordPrettyPrinterPtr = std::make_unique<FormatedRecordPrinter>();
}