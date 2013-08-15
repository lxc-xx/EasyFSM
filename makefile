easyfsm: easyfsm.o lex.o parser.o generator.o easyfsm.h
	g++ -o easyfsm easyfsm.o lex.o parser.o generator.o -g
easyfsm.o: easyfsm.cpp easyfsm.h
	g++ -c -o easyfsm.o easyfsm.cpp -g
generator.o: generator.cpp generator.h easyfsm.h
	g++ -c -o generator.o generator.cpp -g
parser.o: parser.cpp parser.h easyfsm.h
	g++ -c -o parser.o parser.cpp -g
lex.o: lex.cpp parser.h easyfsm.h
	g++ -c -o lex.o lex.cpp -g
parser.cpp parser.h: parser.y
	bison --defines=parser.h parser.y -o parser.cpp
lex.cpp: lex.l
	flex -o lex.cpp lex.l
clean:
	rm lex.cpp lex.o parser.cpp parser.h parser.o easyfsm easyfsm.o generator.o

