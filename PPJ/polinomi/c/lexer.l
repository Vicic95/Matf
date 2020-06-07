%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include "poli.hpp"

#include "parser.tab.hpp"
%}

%%
-?[0-9]+(\.[0-9]+)? {
    yylval.d_vrednost = atof(yytext);
    return br_token;
}
[p][1-9] {
    yylval.s = new std::string(yytext);
    return id_token;
}
[<>,\n:!=()+*-] {
    return *yytext;
}
[ \t] {
}
. {
    std::cerr << "Leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
