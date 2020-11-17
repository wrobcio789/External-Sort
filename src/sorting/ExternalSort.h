#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include "ContignousBufferFiller.h"
#include "TapeManager.h"

class ExternalSort
{
private:
	const Config& _config;

	size_t _firstStageSort(CharBuffer& buffer, TapeManager& tapeManager) const;

	void _secondStageSort(CharBuffer& buffer, size_t recordsCount, TapeManager& tapeManager) const;

public:
	ExternalSort();

	void Sort();
};

