#pragma once
#include <fstream>
#include <algorithm>
#include "../model/Record.h"
#include "../config/Locator.h"
#include "../model/Buffer.h"
#include "../File.h"

class ExternalSort
{
private:
	const Locator& _config;

	void _firstStageSort();

public:
	ExternalSort();

	void Sort();
};

