CC=g++
CFLAGS=-std=c++11 -g -Wall

all: app

app: app.o bst.o website.o
	$(CC) $(CFLAGS) $^ -o $@

app.o: app.cpp bst.h website.h
	$(CC) $(CFLAGS) -c app.cpp

bst.o: bst.cpp bst.h
	$(CC) $(CFLAGS) -c bst.cpp

website.o: website.cpp website.h
	$(CC) $(CFLAGS) -c website.cpp

run: app
	./app

clean:
	rm -f app *.o

valgrind: app
	valgrind --leak-check=full --show-leak-kinds=all ./app
