#include "LocatorConfigurator.h"
#include "../../sorting/Sorting.h"
#include "../../generator/RecordGenerator.h"
#include "../../user_input/UserInput.h"

void LocatorConfigurator::configure(int argsCount, char* args[]) {
	Locator& locator = Locator::get();

	const ArgsParser argsParser(argsCount, args);
	_registerProgram(locator, argsParser);
}

void LocatorConfigurator::_registerProgram(Locator& locator, const ArgsParser& argsParser) {
	const std::string& subprogramName = argsParser.getSubroutineName();
	if (subprogramName == "sort")
		locator.program = std::make_unique<Sorting>(argsParser);
	else if (subprogramName == "generate")
		locator.program = std::make_unique<RecordGenerator>(argsParser);
	else if (subprogramName == "manual")
		locator.program = std::make_unique<UserInput>(argsParser);
}
