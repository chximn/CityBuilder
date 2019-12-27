#pragma once
#include <iostream>
#include <string>

class error {
private:
	static unsigned int line;
	static unsigned int contextus;

public:
	error() = delete;
	static unsigned int get_line();
	static void increment_line();
	static void report(unsigned int, std::string const &);
	static void report(std::string const &);

	static void context(int);
};
