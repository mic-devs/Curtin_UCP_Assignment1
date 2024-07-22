CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -g
OBJ = main.o build.o buffer.o game.o random.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c
	$(CC) -c main.c $(CFLAGS)

build.o : build.c build.h
	$(CC) -c build.c $(CFLAGS)

buffer.o : buffer.c terminal.h
	$(CC) -c buffer.c $(CFLAGS)

game.o : game.c game.h
	$(CC) -c game.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)