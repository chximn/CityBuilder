#include "error.hh"

unsigned int error::line = 1;
unsigned int error::contextus = 0;

unsigned int error::get_line() {
	return line;
}

void error::increment_line() {
	line++;
}

void error::report(unsigned int l, std::string const & s) {
	std::cerr << "\nErreur (ligne " << l << "): " << s << "\n";
	exit(-2);
}

void error::report(std::string const & s) {
	if (contextus) {
		report(contextus, s);
		contextus = 0;
	}

	else {
		std::cerr << "\nErreur: " << s << "\n";
		exit(-3);
	}
}

void error::context(int c) {
	contextus = c;
}
