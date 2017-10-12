
ThreadedRing: ThreadedRing.c 
	gcc ThreadedRing.c -lpthread -o ThreadedRing.o

all: ThreadedRing

clean:
	rm -rf *.o	
