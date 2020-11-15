#pragma once
#include "../model/Buffer.h"
#include "../config/Locator.h"
#include "../io/ConstrainedFile.h"
#include "../model/RecordComparators.h"

class ContignousBufferFiller
{
private:
	RecordBuffer _buffer;
	size_t _elementIndex;
	ConstrainedFile _file;

	void _updatePositions();

	void _readData();

public:
	ContignousBufferFiller() = default;

	ContignousBufferFiller(RecordBuffer buffer, ConstrainedFile file);

	Record pop();
	Record peek() const;
	bool hasNext() const;

	bool operator<(const ContignousBufferFiller& other);
};

