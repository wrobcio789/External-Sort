#include "PrettyOutput.h"
#include "../../config//Locator.h"


void PrettyOutput::print(const std::string& filename)
{
	const Config& config = Locator::get().config;
	
	std::string prettyFilename = filename + config.prettyFileSuffix;
	const SingleRecordPrinter& recordPrinter = *(config.recordPrettyPrinterPtr);


	std::ofstream output(prettyFilename);
	std::ifstream input(filename, std::ios_base::binary);

	if (output.is_open() && input.is_open())
		_printUnchecked(recordPrinter, input, output);
}

void PrettyOutput::_printUnchecked(const SingleRecordPrinter& recordPrinter, std::ifstream& input, std::ofstream& output) {
	recordPrinter.initStreams(input, output);
	while (input.peek() != EOF) {
		recordPrinter.print(input, output);
	}
}