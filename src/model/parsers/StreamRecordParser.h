#pragma once
#include "StreamObjectParser.h"
#include "../Record.h"

class StreamRecordParser : public StreamObjectParser<Record> {

public:
	Record read(std::istream & input) const override;
	void write(std::ostream & output, const Record& record) const override;
};