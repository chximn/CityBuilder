%skeleton "lalr1.cc"
%require "3.0"

%defines
%define parser_class_name { Parser }
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
	#include "command.hh"

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

	int calculate(ExpressionPtr, Driver const &);
}

%token NEIGHBOR HOUSE ROAD CONSTRUCT TURN ORIENTATE MOVE DESTRUCT POSITION ORIENTATION NEIGHBORHOOD HOUSELIST COLORIZE COLOR_OF
%token <bool> CLOCKWISE
%token <std::string> OTHER
%token ARROW DEGREE
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    COMMENT
%token <std::string>    VAR_NAME
%token <std::string>    COLOR
%type <int>             city_header
%type <ExpressionPtr>   operation
%type <color>           color
%type <degree>          degree
%type <point>           coordinates point
%type <house_ptr>       house
%type <house>           house_construction
%type <command_ptr>     command
%left '-' '+'
%left '*' '/'
%precedence  NEG

%%

program:
		 comment NL program |
		 city    NL program |
		         NL program |
	     END {
		 	driver.show();
			YYACCEPT;
		 }

city:
 	city_header '{' NL commands '}'
	{
		std::cout << "construire ville de taille: " << $1 << "\n";
		driver.get_city().set_radius($1);
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
	house_construction {
		std::cout << "house construction: " << $1.to_string() << "\n";
		// driver.get_city().add_house($1);
		$$ = std::make_shared<commands::construct_house>($1);
	} |

	ROAD house ARROW house {
		std::cout << "road: " << $2->to_string() << " -> " << $4->to_string() << "\n";
        $2->add_neighbor($4);$4->add_neighbor($2);
    } |

	DESTRUCT house {
		std::cout << "destruct house: " << $2->to_string() << "\n";
		driver.get_city().remove_house(*$2);
	} |

	POSITION house {
		std::cout << "show house: " << $2->to_string() << "\n";
		std::cout << "position: " << $2->get_coordinates().to_string() << "\n";
	} |

	TURN house CLOCKWISE {
		std::cout << "turn house: " << $2->to_string() << ", clockwise: " << $3 << "\n";
		$2->get_orientation().turn($3);
	} |

	NEIGHBORHOOD house {
		std::cout << "neighborhood of: " << $2->to_string() << '\n';
        std::vector<house_ptr> p=$2->get_neighbors();
        for(auto const & pp:p)
            std::cout << "-"<< pp->to_string() << "distance : " << $2->distance(pp) << "\n";
	} |

	ORIENTATE house degree {
		std::cout << "orientate house in: " << $2->to_string() << " to " << $3.to_string() << "\n";
		$2->get_orientation() = $3;
	} |

	MOVE house ARROW coordinates {
		std::cout << "move house: " << $2->to_string() << " to " << $4.to_string() << "\n";
		$2->get_coordinates() = $4;
	} |

    assignment {

	} |

    COLORIZE house color {
        std::cout << "color of " << $2->to_string() << " is " << color($3).to_string() << " now \n";
		$2->get_color() = $3;
	} |

    COLOR_OF house {
        std::cout << "color is " << $2->get_color().to_string() << " \n";
    } |

	NEIGHBOR house operation {
		int distance = calculate($3, driver);
		house_ptr hp = driver.get_city().add_neighbor($2, distance);
		std::cout << "add random neighbour, with distance of " << distance << "\n";
		std::cout << "new neighbour: " << hp->to_string() << "\n";
	}

house_construction:
	HOUSE {
		$$ = house();
	} |

	HOUSE coordinates {
		$$ = house($2);
	} |

	HOUSE VAR_NAME coordinates {
		$$ = house($3, degree(0), $2);
	} |

	HOUSE VAR_NAME {
		$$ = house(point(0, 0, 0), degree(0), $2);
	}

assignment:
    VAR_NAME '=' operation {
        std::cout << "affectation: " << $1 << " = " << calculate($3, driver) << "\n";
        driver.setVariable($1, calculate($3, driver));
    }
comment:
	COMMENT {
		std::cout << "Comment: " << $1 << std::endl;
	}

house:
	HOUSELIST '[' operation ']' {
		$$ = driver.get_city().get_house(calculate($3, driver));
	} |

    VAR_NAME {
        $$ = driver.get_city().get_house($1);
    } |

	coordinates {
		$$ = driver.get_city().get_house($1);
	}

color:
	COLOR {
		$$ = color($1);
	} |

	point {
		$$ = color($1);
	}

degree:
	operation DEGREE {
		$$ = degree(calculate($1, driver));
	}

coordinates: point

point:
	'(' operation ',' operation ',' operation ')' {
		$$ = point(calculate($2, driver), calculate($4, driver), calculate($6, driver));
	}

operation:
	VAR_NAME {
      $$ = std::make_shared<Variable>($1);
    } |
    NUMBER {
     $$ = std::make_shared<Constante>($1);
    } |
    operation '+' operation {
       $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::plus);
   } |
   operation '-' operation  {
      $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::moins);
   } |
   operation '/' operation  {
       $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::divise);
   } |
   operation '*' operation  {
       $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::multiplie);
   } |
   '-' operation %prec NEG {
         $$ = std::make_shared<ExpressionUnaire>($2,OperateurUnaire::neg);
     }

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}

int calculate(ExpressionPtr p, Driver const & d) {
	return p->calculer(d.getContexte());
}
