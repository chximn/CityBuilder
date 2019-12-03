%{

#include "scanner.hh"
#include <string>
#include <cstdlib>

#define YY_NO_UNISTD_H

using token = yy::Parser::token;

#undef  YY_DECL
#define YY_DECL int Scanner::yylex( yy::Parser::semantic_type * const lval, yy::Parser::location_type *loc )

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option c++
%option yyclass="Scanner"
%option noyywrap

%%
%{
    yylval = lval;
%}

<<EOF>> return token::END;

"+"           return '+';
"*"           return '*';
"-"           return '-';
"/"           return '/';
"("           return '(';
")"           return ')';
"="           return '=';
"{"           return '{';
"}"           return '}';
","           return ',';
"->"          return token::ARROW;
"["           return '[';
"]"           return ']';
"°"           return token::DEGREE;
"Maison"      return token::HOUSE;
"Route"       return token::ROAD;
"Construire"  return token::CONSTRUCT;
"Tourner"     return token::TURN;
"Orienter"    return token::ORIENTATE;
"Deplacer"    return token::MOVE;
"Detruire"    return token::DESTRUCT;
"Position"    return token::POSITION;
"Orientation" return token::ORIENTATION;
"Voisinage"   return token::NEIGHBORHOOD;
"maison"      return token::HOUSELIST;
"Coloriser"   return token::COLORIZE;
"Couleur"     return token::COLOR_OF;
"horaire" {
	yylval->build<bool>(true);
	return token::CLOCKWISE;
}

"!horaire" {
	yylval->build<bool>(false);
	return token::CLOCKWISE;
}

(\%\%(.|[ ])+) {
	std::cout << "inline comment\n";
	yylval->build<std::string>(YYText());
	return token::COMMENT;
}
(\%\/\n([ ]|[^"%/"]|\n)*+\n\/\%) {
	std::cout << "multiline comment\n";
	yylval->build<std::string>(YYText());
	return token::COMMENT;
}

[0-9]+      {
    yylval->build<int>(std::atoi(YYText()));
    return token::NUMBER;
}
[a-zA-Z_][0-9a-zA-Z_]*      {
    yylval->build<std::string>(YYText());
    return token::VAR_NAME;
}
"\n"          {
    loc->lines();
    return token::NL;
}
#[0-9a-f]{6}    {
    yylval->build<std::string>(YYText());
    return token::COLOR;
}

%%
