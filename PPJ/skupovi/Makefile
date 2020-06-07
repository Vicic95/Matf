skupovi: lex.yy.c parser.tab.cpp zadatak.cpp
	g++ -o skupovi -Wall -Wextra -std=c++11 lex.yy.c parser.tab.cpp zadatak.cpp
	
lex.yy.c: lexer.l
	flex lexer.l
	
parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -v -d parser.ypp
	
.PHONY: clean

clean:
	rm *.tab.* *.c *.output skupovi
