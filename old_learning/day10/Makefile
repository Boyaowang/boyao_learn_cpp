inc = ./include/

pets: shops.o namespace.o
	g++ shops.o namespace.o -o pets

namespace.o: namespace.cpp
	g++ -I $(inc) -c namespace.cpp

shops.o: shops.cpp $(inc)shops.h
	g++ -I $(inc) -c shops.cpp

clean:
	rm *.o pets
