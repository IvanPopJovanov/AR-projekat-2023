

main: main.o parser.o lexer.o fol.o rewrite.o substitution.o
	g++ -std=c++17 -o main fol.o main.o parser.o lexer.o  rewrite.o substitution.o

fol.o: fol.cpp fol.hpp


main.o: main.cpp fol.hpp Rewrite.h Substitution.h
	g++ -std=c++17 -c -o main.o main.cpp

parser.o: parser.cpp fol.hpp
	g++ -std=c++17 -c -o parser.o parser.cpp

lexer.o: lexer.cpp parser.hpp
	g++ -std=c++17 -c -o lexer.o lexer.cpp

rewrite.o: Rewrite.cpp Rewrite.h fol.hpp
	g++ -std=c++17 -c -o rewrite.o Rewrite.cpp

substitution.o: Substitution.cpp Substitution.h fol.hpp
	g++ -std=c++17 -c -o substitution.o Substitution.cpp

clean:
	rm -f *.o
	rm -f *~
	rm -f parser.cpp
	rm -f lexer.cpp
	rm -f parser.hpp
	rm -f main
