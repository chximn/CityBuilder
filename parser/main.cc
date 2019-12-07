#include "parser.hpp"
#include "scanner.hh"
#include "driver.hh"
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>

#include <cstring>

int main( int  argc, char* argv[]) {
	// Random
	srand((unsigned) time(0));

    // Global
    Driver driver;

    // Flex
    Scanner scanner(std::cin, std::cout);

    // Bison
    yy::Parser parser(scanner, driver);

    parser.parse();

    return 0;
}
