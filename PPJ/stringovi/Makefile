zadatak: lex.yy.c parser.tab.cpp
	g++ -o zadatak -std=c++11 -Wall -Wextra lex.yy.c parser.tab.cpp
	
lex.yy.c: lexer.l
	flex lexer.l
	
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp
	
.PHONY: clean

clean: 
	rm *.tab.* *.output *.c zadatak
