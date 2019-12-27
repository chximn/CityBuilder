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
	#include <utility>
	#include "error.hh"

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

%token NEIGHBOR HOUSE ROAD TURN ORIENTATE MOVE DESTRUCT POSITION ORIENTATION NEIGHBORHOOD HOUSELIST COLORIZE COLOR_OF
%token CONSTRUCT IF WHILE FOR REPEAT
%token <bool> CLOCKWISE
%token <std::string> OTHER
%token ARROW DEGREE
%token AND OR EQUAL LE GE ELSE VOID  OCCUPIED EMPTY  RTIMES
%type <std::vector<std::string>> arguments
%type <std::vector<ExpressionPtr>> args
%type <std::pair<std::string, std::vector<std::string>>> function_header
%token DIRECTED PCC TARJAN KRUSKAL WELSH_POWELL
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    COMMENT
%token <std::string>    VAR_NAME
%token <std::string>    COLOR
%type <ExpressionPtr>   city_header
%type <ExpressionPtr>   condition
%type <ExpressionPtr>   operation boolean
%type <color_ref_ptr>   color
%type <degree_ref_ptr>  degree
%type <point_ref_ptr>   coordinates point
%type <house_ref_ptr>   house
%type <house_ref_ptr>   house_construction
%type <commands::command_ptr>     command city
%type <std::vector<commands::command_ptr>> commands body
%type <commands::command_ptr> assignment
%type <std::vector<commands::command_ptr>> program

%left '-' '+'
%left '*' '/'
%left '<' '>' EQUAL LE GE
%left AND OR


%precedence  NO
%precedence  NEG

%%

entry:
	program {
		std::cout << "\n";

		for (auto const & c : $1) {
			c->execute(driver.get_city(), driver.getContexte());
		}

		driver.show();
		YYACCEPT;
	}

program:
		 comment  NL program { $$ = $3; } |
		 city     NL program { $3.insert($3.begin(), $1); $$ = $3; } |
		 function NL program { $$ = $3; } |
		          NL program { $$ = $2; } |
	     END { $$ = std::vector<commands::command_ptr>{}; }

city:
 	city_header '{' NL commands '}'
	{
		$$ = std::make_shared<commands::city_construction>($1, $4);
	}

city_header:
	CONSTRUCT '(' operation ')' { $$ = $3; } |
	CONSTRUCT                   { $$ = std::make_shared<Constante>(5);  }

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

	FOR '(' assignment ';' operation ';' assignment ')' body {
		$$ = std::make_shared<commands::for_loop>($3, $5, $7, $9);
	} |

	house_construction {
		$$ = std::make_shared<commands::construct_house>($1);
	} |

	ROAD house ARROW house {
		$$ = std::make_shared<commands::construct_road>($2, $4);
    } |

    DESTRUCT house ARROW house {
        $$ = std::make_shared<commands::destruct_road>($2,$4);
    } |

	ROAD house ARROW house DIRECTED {
		$$ = std::make_shared<commands::construct_road>($2, $4, true);
	} |


	DESTRUCT house {
		$$ = std::make_shared<commands::destruct_house>($2);
	} |

	POSITION house {
		$$ = std::make_shared<commands::position_house>($2, std::cout);
	} |

	TURN house CLOCKWISE {
		$$ = std::make_shared<commands::turn_house>($2, $3);
	} |

	NEIGHBORHOOD house {
		$$ = std::make_shared<commands::show_neighborhood>($2, std::cout);
	} |

	ORIENTATE house degree {
		$$ = std::make_shared<commands::orientate_house>($2, $3);
	} |

    ORIENTATION house {
        $$ = std::make_shared<commands::orientation_house>($2, std::cout);
    } |

	MOVE house ARROW coordinates {
		$$ = std::make_shared<commands::move_house>($2, $4);
	} |

	assignment {
		$$ = $1;
	} |

    COLORIZE house color {
		$$ = std::make_shared<commands::colorize_house>($2, $3);
	} |

    COLOR_OF house {
		$$ = std::make_shared<commands::show_color>($2, std::cout);
	} |

	NEIGHBOR house operation {
		$$ = std::make_shared<commands::add_neighbor>($2, $3);
	} |

	VAR_NAME '(' args ')' {
		$$ = std::make_shared<commands::function_call>($1, $3, driver.get_functions());
	} |

	PCC house ARROW house {
		$$ = std::make_shared<commands::pcc>($2, $4, std::cout);
	} |

	TARJAN {
		$$ = std::make_shared<commands::tarjan_algorithm>();
	} |

	KRUSKAL {
		$$ = std::make_shared<commands::kruksal_algorithm>();
	} |

	WELSH_POWELL {
		$$ = std::make_shared<commands::welsh_powell_algorithm>();
	}

assignment:
	VAR_NAME '=' operation {
		$$ = std::make_shared<commands::assignment>($1, $3);
	}

house_construction:
	HOUSE {
		$$ = std::make_shared<house_ref_create_random>("");
	} |

	HOUSE coordinates {
		$$ = std::make_shared<house_ref_create>("", $2);
	} |

	HOUSE VAR_NAME coordinates {
		$$ = std::make_shared<house_ref_create>($2, $3);
	} |

	HOUSE VAR_NAME {
		$$ = std::make_shared<house_ref_create_random>($2);
	}

args:
	operation ',' args {
		$3.insert($3.begin(), $1);
		$$ = $3;
	} |

	operation {
		$$ = std::vector<ExpressionPtr>{$1};
	}

arguments:
    VAR_NAME ',' arguments {
		$3.insert($3.begin(), $1);
		$$ = $3;
	} |

	VAR_NAME {
		$$ = std::vector<std::string>{$1};
	}

function:
 	function_header body {
		driver.add_function(commands::function($1.first, $1.second, $2));
	}

function_header:
	VOID VAR_NAME '(' arguments ')' {
		$$ = std::pair<std::string, std::vector<std::string>>{$2, $4};
	} |

	VOID VAR_NAME {
		$$ = std::pair<std::string, std::vector<std::string>>{$2, std::vector<std::string>{}};
	}

comment:
	COMMENT {
		// this is a useless comment :)
	}

house:
	HOUSELIST '[' operation ']' {
		$$ = std::make_shared<house_ref_index>($3);
	} |

    VAR_NAME {
		$$ = std::make_shared<house_ref_name>($1);
    } |

	coordinates {
		$$ = std::make_shared<house_ref_coordinates>($1);
	}

color:
	COLOR {
		$$ = std::make_shared<color_ref_hex>($1);
	} |

	point {
		$$ = std::make_shared<color_ref_point>($1);
	}

degree:
	operation DEGREE {
		$$ = std::make_shared<degree_ref>($1);
	}

coordinates: point

point:
	'(' operation ',' operation ',' operation ')' {
		$$ = std::make_shared<point_ref>($2, $4, $6);
	}

operation:
	VAR_NAME {
		$$ = std::make_shared<Variable>($1);
    } |

	NUMBER {
		$$ = std::make_shared<Constante>($1);
    } |

    '(' operation ')' {
	    $$ = $2;
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

	| boolean

boolean:
	operation '<' operation  {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::inf);
	} |

	operation '>' operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::sup);
	} |

	operation EQUAL operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::equ);
	} |

	operation LE operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::inf_equ);
	} |

	operation GE operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::sup_equ);
	} |

	operation OR operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::ou);
	} |

	operation AND operation {
		$$ = std::make_shared<ExpressionBinaire>($1,$3, OperateurBinaire::et);
	} |

	'!' operation %prec NO {
		$$ = std::make_shared<ExpressionUnaire>($2,OperateurUnaire::non);
	} |

	OCCUPIED point {
		$$ = std::make_shared<ExpressionOccupied>(std::make_shared<house_ref_coordinates>($2), driver.get_city());
	} |

	EMPTY point {
		auto occup = std::make_shared<ExpressionOccupied>(std::make_shared<house_ref_coordinates>($2), driver.get_city());
		$$ = std::make_shared<ExpressionUnaire>(occup, OperateurUnaire::non);
	}

%%

void yy::Parser::error(const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
	exit(-1);
}
