CC = gcc
CFLAGS =
LDFLAGS = 
INCLUDES = 
EXEC = towerDefence
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)