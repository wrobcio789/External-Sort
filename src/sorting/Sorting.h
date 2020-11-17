#pragma once
#include "../common/Subprogram.h"
#include "../config/ArgsParser.h"
#include "../config/Locator.h"

class Sorting : public Subprogram
{
private:
	Config& _config;

public:
	Sorting(const ArgsParser& args);

	void run() override;
};

