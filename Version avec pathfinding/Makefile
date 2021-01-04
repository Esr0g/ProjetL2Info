CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LDFLAGS = `sdl2-config --cflags --libs`
LIB = -lSDL2_gfx -lSDL2_ttf
INCLUDES = 
EXEC = towerDefence
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIB)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) $(LIB)

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)