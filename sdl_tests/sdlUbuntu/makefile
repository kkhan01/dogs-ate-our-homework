# CC Specifies Compiler we're using
CC=gcc

# Things to compile
SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

# Libraries to include in the compile
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image

# Output name
OUTPUT=game

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $<
	
clean:
	rm *.o
	rm $(OUTPUT)