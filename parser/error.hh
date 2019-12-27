#pragma once
#include <iostream>
#include <string>

class error {
private:
	static unsigned int line;

public:
	error() = delete;
	static void increment_line();
	static void report(unsigned int, std::string const &);
};
