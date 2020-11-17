#pragma once
#include "Locator.h"
#include "../io/printers/FormatedRecordPrinter.h"
#include "../model/parsers/StreamRecordParser.h"
#include "ArgsParser.h"

class LocatorConfigurator
{
private:
	static void _registerProgram(Locator& locator, const ArgsParser& argsParser);

public:
	static void configure(int argsCount, char* args[]);
};

