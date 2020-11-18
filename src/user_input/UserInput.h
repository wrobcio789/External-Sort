#pragma once
#include "../common/Subprogram.h"
#include "../common/config/Locator.h"
#include "../common/config/ArgsParser.h"
class UserInput : public Subprogram {
private:
	Config& _config;

public:
	UserInput(const ArgsParser& argsParser);

	void run() override;
};

