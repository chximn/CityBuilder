#include "contexte.hh"

int& Contexte::get(const std::string & nom) {
    return variables[nom];
}

const int& Contexte::get(const std::string & nom) const {
    return variables.at(nom);
}

int& Contexte::operator[](const std::string & nom) {
    return variables[nom];
}

const int& Contexte::operator[](const std::string & nom) const {
    return variables.at(nom);
}

void Contexte::show(std::ostream & os) {
	for (auto const & v : variables) {
		os << v.first << ":" << v.second << "\n";
	}
}
