#include "Sorting.h"
#include "ExternalSort.h"
#include "../common/io/printers/PrettyOutput.h"
#include "../common/io/printers/FormatedRecordPrinter.h"

Sorting::Sorting(const ArgsParser& args)
	:	_config(Locator::get().config)
{
	if (!args.isArgumentSpecified("input"))
		throw ArgumentUnspecified("input");
	if (!args.isArgumentSpecified("output"))
		throw ArgumentUnspecified("output");

	_config.isInteractive = args.isFlagSet("i");
	_config.shouldPrettyPrint = args.isFlagSet("pretty");

	_config.bufferCount = args.getValue("buffers").asLongLong(100);
	_config.pageSize = args.getValue("page").asLongLong(4000);
	_config.inputFilename = args.getValue("input").asString();
	_config.outputFilename = args.getValue("output").asString();

	_config.prettyFileSuffix = ".pretty.txt";
	_config.tmpFileSuffix = ".tmp";
	_config.recordPrettyPrinterPtr = std::make_unique<FormatedRecordPrinter>();
}

void Sorting::run() {
	ExternalSort().Sort();
	if (_config.shouldPrettyPrint) {
		PrettyOutput::print(_config.inputFilename);
		PrettyOutput::print(_config.outputFilename);
	}
}
