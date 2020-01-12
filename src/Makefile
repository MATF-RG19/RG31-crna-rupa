PROGRAM = hole
CC      = gcc
CFLAGS  = -g -std=c99 -ansi -Wall -Wextra -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib ./move.h ./drawSceen.h
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o move.o drawSceen.o image.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o move.o drawSceen.o image.o $(LDLIBS)
	
main.o: main.c
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c -o main.o $(LDLIBS)

move.o: move.c
	$(CC) $(CFLAGS) $(LDLIBS) -c move.c -o move.o $(LDLIBS)

drawSceen.o: drawSceen.c
	$(CC) $(CFLAGS) $(LDLIBS) -c drawSceen.c -o drawSceen.o $(LDLIBS)

image.o: image.c
	$(CC) $(CFLAGS) $(LDLIBS) -c image.c -o image.o $(LDLIBS)

	
.PHONY: beauty clean dist

beauty:
	-indent -nut -kr main.c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
