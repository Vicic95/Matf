%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <vector>
#include "zadatak.hpp"

#include "parser.tab.hpp"

%}

%%
disp { return disp_token;}
size { return size_token;}

-?[0-9]|([1-9][0-9]+) {
    yylval.broj_type = atoi(yytext);
    return broj_token;
}
[a-zA-Z] {
    if(((*yytext)>='a') && ((*yytext)<='z')){
        yylval.string_type = *yytext;
        return id_token;
    }
    else{
        yylval.string_type = *yytext + ('a' - 'A');
        return id_token;
    }
}
".+" {return sabiranje_token;}
".*" {return mnozenje_token;}
[\[\](),;\n=] {
    return *yytext;
}
[\t ] {
}
. {
    std::cerr << "Leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
