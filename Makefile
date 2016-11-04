BINS=main
OBJS=main.o app.o
CFLAGS=-O2 -g
CC=gcc
LIBS=-framework OpenGL -lGLEW -lSDL2

all: $(BINS)

.PHONY = all clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm *.o main
