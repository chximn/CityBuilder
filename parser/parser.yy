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
	#include "color.hh"
	#include "degree_ref.hh"
	#include "point_ref.hh"
	#include "color_ref.hh"
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

	int calculate(ExpressionPtr, Driver &);
}

%token NEIGHBOR HOUSE ROAD CONSTRUCT TURN ORIENTATE MOVE DESTRUCT POSITION ORIENTATION NEIGHBORHOOD HOUSELIST COLORIZE COLOR_OF
%token <bool> CLOCKWISE
%token <std::string> OTHER
%token ARROW DEGREE
%token AND OR IF ELSE VOID WHILE OCCUPIED EMPTY REPEAT RTIMES
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    COMMENT
%token <std::string>    VAR_NAME
%token <std::string>    COLOR
%type <int>             city_header
%type <ExpressionPtr>   condition
%type <ExpressionPtr>   operation
%type <color_ref_ptr>   color
%type <degree_ref_ptr>  degree
%type <point_ref_ptr>   coordinates point
%type <house_ref_ptr>   house
%type <house_ref_ptr>   house_construction
%type <commands::command_ptr>     command
%type <std::vector<commands::command_ptr>> commands body
%left '-' '+'
%left '*' '/'
%precedence  NO
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
 	city_header '{' NL commands '}' NL function
	{
		std::cout << "construire ville de taille: " << $1 << "\n";
		driver.get_city().set_radius($1);
		for (auto const & c : $4) {
			c->execute(driver.get_city(), driver.getContexte());
		}
	}

city_header:
	CONSTRUCT '(' NUMBER ')' { $$ = $3; } |
	CONSTRUCT                { $$ = 5;  }

commands:
	comment NL commands {
		$$ = $3;
	} |

	command comment NL commands {
		$4.insert($4.begin(), $1);
		$$ = $4;
	} |

	command NL commands {
		$3.insert($3.begin(), $1);
		$$ = $3;
	} |

	comment NL {
		$$ = std::vector<commands::command_ptr>();
	} |

	command comment NL {
		auto v = std::vector<commands::command_ptr>();
		v.push_back($1);
		$$ = v;
	} |

	command NL {
		auto v = std::vector<commands::command_ptr>();
		v.push_back($1);
		$$ = v;
	} |

	NL commands {
		$$ = $2;
	} |

	NL {
		$$ = std::vector<commands::command_ptr>();
	}

body: '{' NL commands '}' {
	$$ = $3;
}

condition : '(' operation ')' {
	$$ = $2;
}

command:
	IF condition body NL {
		$$ = std::make_shared<commands::if_condition>($2, $3);
	} |

	IF condition body NL ELSE body {
		$$ = std::make_shared<commands::if_else_condition>($2, $3, $6);
	} |

	WHILE condition body {
		$$ = std::make_shared<commands::while_loop>($2, $3);
	} |

	REPEAT operation RTIMES body {
		$$ = std::make_shared<commands::repeat_loop>($2, $4);
	} |

	house_construction {
		std::cout << "house construction" << "\n";
		// driver.get_city().add_house($1);
		$$ = std::make_shared<commands::construct_house>($1);
	} |

	ROAD house ARROW house {
		std::cout << "road" << "\n";
        // $2->add_neighbor($4);$4->add_neighbor($2);
		$$ = std::make_shared<commands::construct_road>($2, $4);
    } |

	DESTRUCT house {
		std::cout << "destruct house" << "\n";
		// driver.get_city().remove_house(*$2)
		$$ = std::make_shared<commands::destruct_house>($2);
	} |

	POSITION house {
		std::cout << "show house" << "\n";
		// std::cout << "position: " << $2->get_coordinates().to_string() << "\n";
		$$ = std::make_shared<commands::position_house>($2, std::cout);
	} |

	TURN house CLOCKWISE {
		std::cout << "turn house" << "\n";
		// $2->get_orientation().turn($3);
		$$ = std::make_shared<commands::turn_house>($2, $3);
	} |

	NEIGHBORHOOD house {
		std::cout << "neighborhood" << '\n';
        // std::vector<house_ptr> p=$2->get_neighbors();
        // for(auto const & pp:p)
        //     std::cout << "-"<< pp->to_string() << "distance : " << $2->distance(pp) << "\n";
		$$ = std::make_shared<commands::show_neighborhood>($2, std::cout);
	} |

	ORIENTATE house degree {
		std::cout << "orientate house\n";
		// $2->get_orientation() = $3;
		$$ = std::make_shared<commands::orientate_house>($2, $3);
	} |

	MOVE house ARROW coordinates {
		std::cout << "move house\n";
		// $2->get_coordinates() = $4;
		$$ = std::make_shared<commands::move_house>($2, $4);
	} |

	VAR_NAME '=' operation {
        std::cout << "affectation" << "\n";
		$$ = std::make_shared<commands::assignment>($1, $3);
        // driver.setVariable($1, calculate($3, driver));
    } |

    COLORIZE house color {
        std::cout << "change color\n";
		// $2->get_color() = $3;
		$$ = std::make_shared<commands::colorize_house>($2, $3);
	} |

    COLOR_OF house {
		std::cout << "show color" << "\n";
        // std::cout << "color is " << $2->get_color().to_string() << " \n";
		$$ = std::make_shared<commands::show_color>($2, std::cout);
	} |

	NEIGHBOR house operation {
		std::cout << "add random neighbour\n";
		// int distance = calculate($3, driver);
		// house_ptr hp = driver.get_city().add_neighbor($2, distance);
		// std::cout << "new neighbour: " << hp->to_string() << "\n";
		$$ = std::make_shared<commands::add_neighbor>($2, $3);
	}

house_construction:
	HOUSE {
		auto zero = std::make_shared<Constante>(0);
		auto p0 = std::make_shared<point_ref>(zero, zero, zero);
		$$ = std::make_shared<house_ref_create>("", p0);
		// $$ = house();
	} |

	HOUSE coordinates {
		$$ = std::make_shared<house_ref_create>("", $2);
		// $$ = house($2);
	} |

	HOUSE VAR_NAME coordinates {
		$$ = std::make_shared<house_ref_create>($2, $3);
		// $$ = house($3, degree(0), $2);
	} |

	HOUSE VAR_NAME {
		auto zero = std::make_shared<Constante>(0);
		auto p0 = std::make_shared<point_ref>(zero, zero, zero);
		$$ = std::make_shared<house_ref_create>($2, p0);
		// $$ = house(point(0, 0, 0), degree(0), $2);
	}
argument:
    VAR_NAME |argument
function:
    VOID VAR_NAME '(' argument ')'  {
        
}

comment:
	COMMENT {
		std::cout << "Comment: " << $1 << std::endl;
	}

house:
	HOUSELIST '[' operation ']' {
		// $$ = driver.get_city().get_house(calculate($3, driver));
		$$ = std::make_shared<house_ref_index>($3);
	} |

    VAR_NAME {
        // $$ = driver.get_city().get_house($1);
		$$ = std::make_shared<house_ref_name>($1);
    } |

	coordinates {
		// $$ = driver.get_city().get_house($1);
		$$ = std::make_shared<house_ref_coordinates>($1);
	}

color:
	COLOR {
		// $$ = color($1);
		$$ = std::make_shared<color_ref_hex>($1);
	} |

	point {
		// $$ = color($1);
		$$ = std::make_shared<color_ref_point>($1);
	}

degree:
	operation DEGREE {
		// $$ = degree(calculate($1, driver));
		$$ = std::make_shared<degree_ref>($1);
	}

coordinates: point

point:
	'(' operation ',' operation ',' operation ')' {
		// $$ = point(calculate($2, driver), calculate($4, driver), calculate($6, driver));
		$$ = std::make_shared<point_ref>($2, $4, $6);
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
     } |
     operation '=' '=' operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$4, OperateurBinaire::equ);
     } |
     operation '<' operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::inf);
     } |
     operation '>' operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::sup);
     } |
     operation '<' '=' operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$4, OperateurBinaire::inf_equ);
     } |
     operation '>' '=' operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$4, OperateurBinaire::sup_equ);
     } |
     '!' operation %prec NO {
           $$ = std::make_shared<ExpressionUnaire>($2,OperateurUnaire::non);
     } |
     operation OR operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::ou);
     } |
     operation AND operation {
         $$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::et);
     } |

	 OCCUPIED point {
		 $$ = std::make_shared<ExpressionOccupied>(std::make_shared<house_ref_coordinates>($2), driver.get_city());
	 } |

	 EMPTY point {
		 auto occup = std::make_shared<ExpressionOccupied>(std::make_shared<house_ref_coordinates>($2), driver.get_city());
		 $$ = std::make_shared<ExpressionUnaire>(occup, OperateurUnaire::non);
	 }

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}

int calculate(ExpressionPtr p, Driver & d) {
	return p->calculer(d.getContexte());
}
