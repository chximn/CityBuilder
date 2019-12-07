#include "parser.hpp"
#include "scanner.hh"
#include "driver.hh"
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>

#include <QtGui>
#include <QApplication>

#include <cstring>

int main( int argc, char **argv) {
	srand((unsigned) time(0));

    QApplication app(argc,argv);

    Driver * driver = new Driver;
    Scanner * scanner = new Scanner(std::cin, std::cout);
    yy::Parser * parser = new yy::Parser(*scanner, *driver);

    parser->parse();
    driver->getGUI()->show();
    return app.exec();
}
