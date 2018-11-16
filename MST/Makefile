main: main.o pritree.o
	g++ -g  main.o pritree.o -o main
main.o:main.cpp
	g++ -c -g main.cpp -o main.o
pritree.o:pritree.cpp pritree.hpp
	g++ -c -g pritree.hpp pritree.cpp

clean:
	rm *.o
	rm *.gch
	rm main
