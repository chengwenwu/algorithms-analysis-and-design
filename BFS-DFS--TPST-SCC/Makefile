main:main.o graph.o
	g++ -g main.o graph.o -o main
main.o:main.cpp
	g++ -c -g main.cpp -o main.o
graph.o:graph.hpp graph.cpp
	g++ -c -g graph.hpp graph.cpp

clean:
	del -f *.o
	del -f *.gch
	del main.exe
