#pragma once
#include <fstream>
#include <algorithm>
#include "../config/Locator.h"

class ExternalSort
{
private:
	const Locator& _config;

	void _firstStageSort();

public:
	ExternalSort();

	void Sort();
};

