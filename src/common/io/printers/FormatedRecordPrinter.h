#pragma once
#include "SingleRecordPrinter.h"

class FormatedRecordPrinter : public SingleRecordPrinter
{
public:
	void initStreams(std::istream& input, std::ostream& output) const override;

	void print(std::istream& input, std::ostream& output) const override;
};

