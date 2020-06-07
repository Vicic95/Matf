%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include "zadatak.hpp"

#include "parser.tab.hpp"
%}

%%
kutija { return kutija_token;}
prazna { return prazna_token;}
puna { return puna_token;}
prikazi { return prikazi_token;}

"<-" { return ubaci_token;}
[A-Z] {
    yylval.string_type = new std::string(yytext);
    return id_token;
}
[0-9]|[1-9][0-9]+ {
    yylval.tezina_type = atoi(yytext);
    return tezina_token;
}
-?([0-9]|[1-9][0-9]+)(\.[0-9]+)? {
    yylval.broj_type = atof(yytext);
    return broj_token;

}
[\[\]=,;()-] {

    return *yytext;
}
[\t\n ] {

}
. {
    std::cerr << "Leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
