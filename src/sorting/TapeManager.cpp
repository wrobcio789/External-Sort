#include "TapeManager.h"
#include <filesystem>

TapeManager::TapeManager()
	:	_config(Locator::get().config)
{
	_input = new File(_config.inputFilename, File::OpenMode::READ);
	_operationalInput = new File(_config.outputFilename + ".1" + _config.tmpFileSuffix, File::OpenMode::READ_WRITE);
	_operationalOutput = new File(_config.outputFilename + ".2" + _config.tmpFileSuffix, File::OpenMode::READ_WRITE);
}

TapeManager::~TapeManager()
{
	std::string currentFilename = _operationalOutput->getName();
	std::string temporaryFilename = _operationalInput->getName();

	delete _input;
	delete _operationalInput;
	delete _operationalOutput;

	std::filesystem::remove(std::filesystem::path(temporaryFilename));
	std::filesystem::rename(std::filesystem::path(currentFilename), _config.outputFilename);
}

File* TapeManager::getInput()
{
	return _input;
}

File* TapeManager::getOperationalOutput()
{
	return _operationalOutput;
}

File* TapeManager::getOperationalInput()
{
	return _operationalInput;
}

void TapeManager::swap()
{
	std::swap(_operationalInput, _operationalOutput);
	_operationalInput->reset();
	_operationalOutput->reset();
}

void TapeManager::flush() {
	_operationalInput->flush();
	_operationalOutput->flush();
}
