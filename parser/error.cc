#include "error.hh"

unsigned int error::line = 0;

void error::increment_line() {
	line++;
}

void error::report(unsigned int l, std::string const & s) {
	std::cerr << "Erreur (ligne " << l << "): " << s << "\n";
}
