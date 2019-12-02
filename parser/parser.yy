%skeleton "lalr1.cc"
%require "3.0"

%defines
%define api.parser.class { Parser }
%define api.value.type variant
%define parse.assert

%locations

%code requires{
    #include "contexte.hh"
    #include "expressionBinaire.hh"
    #include "expressionUnaire.hh"
    #include "constante.hh"
    #include "variable.hh"
	#include "point.hh"
	#include "house.hh"

    class Scanner;
    class Driver;
}

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%code{
    #include <iostream>
    #include <string>

    #include "scanner.hh"
    #include "driver.hh"

    #undef  yylex
    #define yylex scanner.yylex
}

%token HOUSE ROAD CONSTRUCT TURN ORIENTATE MOVE DESTRUCT POSITION ORIENTATION NEIGHBORHOOD HOUSELIST CLOCKWISE ANTI_CLOCKWISE
%token <std::string> OTHER
%token ARROW DEGREE
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    COMMENT
%type <int>             city_header
%type <int>             operation
%type <Point>           coordinates
%type <House>           house
%left '-' '+'
%left '*' '/'
%precedence  NEG

%%

program:
		 comment NL program |
		 city    NL program |
		         NL program |
	     END { YYACCEPT; }

city:
 	city_header '{' NL commands '}'
	{
		std::cout << "construire ville de taille: " << $1 << "\n";
	}

city_header:
	CONSTRUCT '(' NUMBER ')' { $$ = $3; } |
	CONSTRUCT                { $$ = 5;  }

commands:
	comment NL commands         |
	command comment NL commands |
	command NL commands         |
	comment NL                  |
	command comment NL          |
	command NL                  |
	        NL commands

command:
	HOUSE coordinates {
		std::cout << "house: " << $2.toString() << "\n";
	} |

	ROAD coordinates ARROW coordinates {
		std::cout << "road: " << $2.toString() << " -> " << $4.toString() << "\n";
	} |

	DESTRUCT house {
		std::cout << "destruct house\n";
	} |

	POSITION house {
		std::cout << "show house\n";
	}

comment:
	COMMENT {
		std::cout << "Comment: " << $1 << std::endl;
	}

house:
	HOUSELIST '[' NUMBER ']' {
		$$ = House();
	}

coordinates:
	'(' operation ',' operation ',' operation ')' {
		$$ = Point($2, $4, $6);
	}

operation:
    NUMBER {
        $$ = $1;
    }
    | '(' operation ')' {
        $$ = $2;
    }
    | operation '+' operation {
        $$ = $1 + $3;
    }
    | operation '-' operation {
        $$ = $1 - $3;
    }
    | operation '*' operation {
        $$ = $1 * $3;
    }
    | operation '/' operation {
        $$ = $1 / $3;
    }
    | '-' operation %prec NEG {
        $$ = - $2;
    }

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
