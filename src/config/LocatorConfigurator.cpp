#include "LocatorConfigurator.h"

void LocatorConfigurator::configure(int argsCount, char* args[]) {
	Locator& locator = Locator::get();

	locator.bufferCount = 1000;
	locator.pageSize = 4096;
	locator.inputFilename = "./data/input1000000.bin";
	locator.outputFilename = "./data/output1000000.bin";

	locator.prettyInputFilename = "./data/pretty_input1000000.txt";
	locator.prettyOutputFilename = "./data/pretty_output1000000.txt";
	locator.recordPrettyPrinterPtr = std::make_unique<FormatedRecordPrinter>();
}