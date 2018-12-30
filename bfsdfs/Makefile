main:main.o bfs.o
	g++ -g main.o bfs.o -o main
main.o:main.cpp
	g++ -c -g main.cpp -o main.o
bfs.o:bfs.hpp bfs.cpp
	g++ -c -g bfs.hpp bfs.cpp 

clean:
	del -f *.o
	del -f *.gch
	del main.exe
	