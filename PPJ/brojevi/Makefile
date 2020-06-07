zadatak: parser.tab.cpp lex.yy.c
	g++ -o zadatak -Wall -Wextra -std=c++11 lex.yy.c parser.tab.cpp
	
parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -v -d parser.ypp
	
lex.yy.c: lexer.l
	flex lexer.l
	
.PHONY: clean

clean:
	rm *.tab.* *.c zadatak *.output
