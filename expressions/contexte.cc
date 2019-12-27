#include "contexte.hh"

int& Contexte::get(const std::string & nom) {
	try { return variables[nom]; }
	catch (...) { error::report("La variable \"" + nom + "\" n'est pas définée ou pas accessible dans ce contexte"); }
	return variables[nom];
}

const int& Contexte::get(const std::string & nom) const {
	try { return variables.at(nom); }
	catch (...) { error::report("La variable \"" + nom + "\" n'est pas définée ou pas accessible dans ce contexte"); }
	return variables.at(nom);
}

int& Contexte::operator[](const std::string & nom) {
	try { return variables[nom]; }
	catch (...) { error::report("La variable \"" + nom + "\" n'est pas définée ou pas accessible dans ce contexte"); }
	return variables[nom];
}

const int& Contexte::operator[](const std::string & nom) const {
	try { return variables.at(nom); }
	catch (...) { error::report("La variable \"" + nom + "\" n'est pas définée ou pas accessible dans ce contexte"); }
	return variables.at(nom);
}

void Contexte::show(std::ostream & os) {
	for (auto const & v : variables) {
		os << v.first << ":" << v.second << "\n";
	}
}
