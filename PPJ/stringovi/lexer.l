%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <cstdlib>

#include "parser.tab.hpp"
%}
%%
string { return string_token;}
reverse { return reverse_token;}
sort { return sort_token;}
upper { return upper_token;}
lower { return lower_token;}
print { return print_token;}
length { return length_token;}
substring { return substring_token;}
"+=" {	return concat_token;}
"==" {	return eq_token;}
[a-z][0-9]* {
    yylval.string_type = new std::string(yytext);
    return id_token;
}
[0-9]|([1-9][0-9]+) {
    yylval.broj_type = atoi(yytext);
    return broj_token;
}
["][^"]+["] {
    std::string* s = new std::string(yytext);
    std::string s1 = s->substr(1,(s->length()-2));
    yylval.string_type = new std::string(s1);
    delete s;
    return string_value_token;
}

[\[\],=();+*"] {
    return *yytext;
}
[\t\n ] {

}
. {
    std::cerr << "Leksicka greska " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
