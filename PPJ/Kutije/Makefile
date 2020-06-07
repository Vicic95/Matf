zadatak: lex.yy.c parser.tab.cpp zadatak.cpp
	g++ -o zadatak -std=c++11 -Wall -Wextra lex.yy.c parser.tab.cpp zadatak.cpp
	
lex.yy.c: lexer.l
	flex lexer.l
	
parser.tab.hpp	parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp
	
.PHONY: clean

clean:
	rm *.tab.* *.c *.output zadatak
