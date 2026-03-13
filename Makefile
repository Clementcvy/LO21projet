prog: main.o fonction.o
	g++ main.o fonction.o -o prog

main.o: main.cpp fonction.h
	g++ -c main.cpp

fonction.o: fonction.cpp fonction.h
	g++ -c fonction.cpp

clean:
	rm -f *.o prog