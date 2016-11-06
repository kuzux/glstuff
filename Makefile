BINS=target/main
OBJS=target/main.o target/app.o target/camera.o target/object.o target/objparse.o
CFLAGS=-O2 -g -Iinclude
CPP=g++
CC=gcc
LIBS=-framework OpenGL -lGLEW -lSDL2

all: $(BINS)

.PHONY = all clean

target/%.o: src/%.c
	mkdir -p target
	$(CC) $(CFLAGS) -c $< -o $@

target/%.o: src/%.cpp
	mkdir -p target
	$(CPP) $(CFLAGS) -c $< -o $@

target/main: $(OBJS)
	mkdir -p target
	$(CPP) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm target/*
