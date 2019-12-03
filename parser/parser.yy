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
	#include "degree.hh"
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

%token HOUSE ROAD CONSTRUCT TURN ORIENTATE MOVE DESTRUCT POSITION ORIENTATION NEIGHBORHOOD HOUSELIST
%token <bool> CLOCKWISE
%token <std::string> OTHER
%token ARROW DEGREE
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    COMMENT
%token <std::string>    VAR_NAME
%type <int>             city_header
%type <int>             operation
%type <degree>          degree
%type <point>           coordinates
%type <house>           house
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
	        NL commands         |
			NL

command:
	HOUSE coordinates {
		std::cout << "house: " << $2.to_string() << "\n";
	} |

  	HOUSE {
		point p(0, 0, 0);
		std::cout << "house: " << p.to_string() << "\n";
	} |
    HOUSE VAR_NAME coordinates  {
      std::cout << $2<<"'s house at "<<$3.to_string()<< "\n";
  }|

	ROAD coordinates ARROW coordinates {
		std::cout << "road: " << $2.to_string() << " -> " << $4.to_string() << "\n";
	} |

	DESTRUCT house {
		std::cout << "destruct house: " << $2.to_string() << "\n";
	} |

	POSITION house {
		std::cout << "show house: " << $2.to_string() << "\n";
	} |


	TURN house CLOCKWISE {
		std::cout << "turn house: " << $2.to_string() << ", clockwise: " << $3 << "\n";
	} |

	NEIGHBORHOOD house {
		std::cout << "neighborhood of: " << $2.to_string() << '\n';
	} |

	ORIENTATE coordinates degree {
		std::cout << "orientate house in: " << $2.to_string() << " to " << $3.to_string() << "\n";
	} |

	MOVE house ARROW coordinates {
		std::cout << "move house: " << $2.to_string() << " to " << $4.to_string() << "\n";
	}



comment:
	COMMENT {
		std::cout << "Comment: " << $1 << std::endl;
	}

house:
	HOUSELIST '[' operation ']' {
		$$ = house();
	}

degree:
	operation DEGREE {
		$$ = degree($1);
	}

coordinates:
	'(' operation ',' operation ',' operation ')' {
		$$ = point($2, $4, $6);
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
