CC=gcc
SRC=$(wildcard *.c)
EXEC=main
OBJ=$(SRC:.c=.o)
LIB=libMaze.a
HEADER=include/$(wildcard *.h)

$(EXEC) : $(OBJ) $(LIB) $(HEADER)
	$(CC) $^ -I include -L. -lmaze -o $@
	# echo $(SRC) $(OBJ)

clean :
	rm $(EXEC) *.o
