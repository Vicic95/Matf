polinom: lex.yy.c parser.tab.cpp poli.cpp
	g++ -o polinom -Wall -Wextra -std=c++11 lex.yy.c parser.tab.cpp poli.cpp
	
lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l
	
parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm *.tab.* *.output polinom *.c
