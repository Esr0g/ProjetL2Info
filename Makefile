CC = gcc
CFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = -lSDL2_gfx
INCLUDES = 
EXEC = towerDefence
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)