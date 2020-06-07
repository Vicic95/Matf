%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <set>
#include "zadatak.hpp"

#include "parser.tab.hpp"
%}

%%
print { return print_token;}
".." { return tt_token;}
check { return check_token;}
card { return card_token;}
-?[0-9]|([1-9][0-9]+) {
    yylval.broj_type = atoi(yytext);
    return broj_token;
}
[A-Z] {
    yylval.string_type = new std::string(yytext);
    return id_token;
}
"\\/" { return unija_token;}
"/\\" { return presek_token;}
"\\" { return razlika_token;}
[={};,-<:] {
    return *yytext;
}

[\t\n ] {

}
. {
    std::cerr << "Leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
