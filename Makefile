BINS=main
OBJS=main.o app.o
CFLAGS=-O2 -g
CPP=g++
CC=gcc
LIBS=-framework OpenGL -lGLEW -lSDL2

all: $(BINS)

.PHONY = all clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

main: $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm *.o main
