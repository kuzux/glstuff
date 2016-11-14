BINS=target/main

OBJS=target/main.o \
target/app.o \
target/camera.o \
target/object.o \
target/objparse.o \
target/mtlparse.o \
target/light.o \
target/geometry.o \
target/scene.o \

TEST_OBJS = target/testing.o \
target/geometry.o \

CFLAGS=-O2 -g -Iinclude -Wall -Werror
CPP=g++
CC=gcc
LIBS= -lGLEW -lSDL2 -ljansson

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS += -lGL
endif
ifeq ($(UNAME_S),Darwin)
    LIBS += -framework OpenGL
endif

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

target/test: $(TEST_OBJS) 
	mkdir -p target
	$(CPP) $(CFLAGS) $(TEST_OBJS) -o $@

test: target/test
	echo '===========Test Results==========='
	./target/test

clean:
	rm target/*
