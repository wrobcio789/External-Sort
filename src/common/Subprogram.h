#pragma once
#include <string>
#include <exception>

class ArgumentUnspecified : public std::exception {
	const std::string _message;

public:
	ArgumentUnspecified(std::string argument) : _message("Argument unspecified: " + argument) {}

	const char* what() const override {
		return _message.c_str();
	}
};

class Subprogram
{
public: 
	virtual void run() = 0;

};

