CFLAGS = -pedantic -O2 -g -std=c++11
LDFLAGS= -lc -lm -std=c++11 -lrt

all: linux-timer-demo


linux-timer-demo.o: linux-timer-demo.cpp
	g++ -o linux-timer-demo.o -c linux-timer-demo.cpp $(CFLAGS)

linux-timer-demo: linux-timer-demo.o
	g++ -o linux-timer-demo linux-timer-demo.o $(LDFLAGS)

clean:
	rm -f *.o linux-timer-demo *~
