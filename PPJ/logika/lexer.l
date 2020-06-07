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

"head" {
    return head_tok;
}
"tail" {
    return tail_tok;
}
[a-z][a-z0-9]* {
    yylval.str_type = new std::string(yytext);
    return id_tok;
}
"/\\" {
    return and_tok;
}
"\\/" {
    return or_tok;
}
"=>" {
    return impl_tok;
    
}
"<=>" {
    return ekv_tok;
}
"True" {
    return true_tok;
}
"False" {
    return false_tok;
    
}
"Undef" {
    return undef_tok;
}
[\n!:()\[\]=] {
    return *yytext;
}
[ \t] {
}
. {
    std::cerr << "leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
