CC=gcc
SRC=$(wildcard *.c)
EXEC=queue
OBJ=$(SRC:.c=.o)
	
$(EXEC) : $(OBJ)
	$(CC) $^ -o $@

clean :
	rm $(EXEC) *.o
