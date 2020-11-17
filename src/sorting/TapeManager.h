#pragma once
#include "../common/config/Locator.h"
#include "../common/io/File.h"

class TapeManager
{
private:
	const Config& _config;

	File* _input;
	File* _operationalInput;
	File* _operationalOutput;

public:
	TapeManager();
	~TapeManager();

	File* getInput();
	File* getOperationalOutput();
	File* getOperationalInput();

	void swap();
};

