CC=gcc
CFLAGS=-lGL -lGLEW -lSDL2 -lSDL2_ttf -lm
FILES=src/*.c src/parser/*.c
PROGRAM=engine

hello:
	$(CC) $(FILES) -o $(PROGRAM) $(CFLAGS)
