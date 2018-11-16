main:main.o bfs.o
	g++ -g main.o bfs.o -o main
main.o:main.cpp
	g++ -c -g main.cpp -o main.o
bfs.o:bfs.hpp bfs.cpp
	g++ -c -g bfs.hpp bfs.cpp 

clean:
	rm -f *.o
	rm -f *.gch
	rm -f *.out
	rm main
	