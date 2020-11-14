#include "PrettyOutput.h"
#include "../../config//Locator.h"


void PrettyOutput::print()
{
	const Locator& config = Locator::get();
	if (config.prettyInputFilename.empty())
		return;

	const SingleRecordPrinter& recordPrinter = *(config.recordPrettyPrinterPtr);

	std::ofstream outputOfOutput(config.prettyOutputFilename);
	std::ifstream inputOfOutput(config.outputFilename, std::ios_base::binary);

	if (inputOfOutput.is_open() && outputOfOutput.is_open())
		_printUnchecked(recordPrinter, inputOfOutput, outputOfOutput);

	std::ofstream outputOfInput(config.prettyInputFilename);
	std::ifstream inputOfInput(config.inputFilename, std::ios_base::binary);

	if (inputOfInput.is_open() && outputOfInput.is_open())
		_printUnchecked(recordPrinter, inputOfInput, outputOfInput);
}

void PrettyOutput::_printUnchecked(const SingleRecordPrinter& recordPrinter, std::ifstream& input, std::ofstream& output) {
	recordPrinter.initStreams(input, output);
	while (input.peek() != EOF) {
		recordPrinter.print(input, output);
	}
}