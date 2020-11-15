#pragma once
#include "../config/Locator.h"
#include "../io/File.h"

class TapeManager
{
private:
	Locator& _config;

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

