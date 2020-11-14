#pragma once
#include "Locator.h"
#include "../io/printers/FormatedRecordPrinter.h"
#include "../model/parsers/StreamRecordParser.h"

class LocatorConfigurator
{
public:
	static void configure(int argsCount, char* args[]);
};

