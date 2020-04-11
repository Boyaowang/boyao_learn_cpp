inc = /include

newdel: newdel.o functions.o
	g++ newdel.o functions.o -o newdel

newdel.o: newdel.cpp
	g++ -c newdel.cpp

functions.o: functions.cpp functions.h
	g++ -I $(inc) -c functions.cpp

clean:
	rm *.o newdel
