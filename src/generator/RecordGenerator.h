#pragma once
#include "../common/Subprogram.h"
#include "../common/config/Locator.h"
#include "../common/config/ArgsParser.h"

class RecordGenerator : public Subprogram {
private:
	Config& _config;

public:

	RecordGenerator(const ArgsParser& argsParser);

	void run() override;
};

