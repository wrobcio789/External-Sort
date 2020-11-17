#pragma once
#include "../common/Subprogram.h"
#include "../common/config/ArgsParser.h"
#include "../common/config/Locator.h"

class Sorting : public Subprogram
{
private:
	Config& _config;

public:
	Sorting(const ArgsParser& args);

	void run() override;
};

