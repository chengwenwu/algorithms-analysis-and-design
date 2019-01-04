main: main.o graph.o pritree.o
	g++ -g  main.o graph.o pritree.o -o main
main.o:main.cpp graph.hpp pritree.hpp
	g++ -c -g main.cpp graph.hpp pritree.hpp
graph.o:graph.cpp graph.hpp pritree.hpp
	g++ -c -g graph.hpp graph.cpp pritree.hpp
pritree.o: pritree.cpp pritree.hpp
	g++ -c -g  pritree.cpp pritree.hpp
clean:
	del *.o
	del *.gch
	del main.exe
