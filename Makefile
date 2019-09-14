project2: main.o llist.o llist.h record2.h
	g++ -o project2 main.o llist.o

project2debug: maindebug.o llistdebug.o llist.h record2.h
	g++ -o project2debug maindebug.o llistdebug.o

main.o: main.cpp llist.h record2.h
	g++ -ansi -pedantic-errors -Wall -c main.cpp

llist.o: llist.cpp llist.h record2.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

maindebug.o: main.cpp
	g++ -D DEBUGMODE -ansi -pedantic-errors -Wall -c main.cpp

llistdebug.o: llist.cpp
	g++ -D DEBUGMODE -ansi -pedantic-errors -Wall -c llist.cpp
