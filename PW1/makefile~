SOURCES = color.c main.c image.c ppm.c
OBJECTS = $(SOURCES:.c=.o)
run : $(OBJECTS)
	gcc $(OBJECTS) -o $@
	
%.o : %.c
	gcc -c $^ -o $@
	
tamiz : $(OBJECTS)
	rm $(OBJECTS)
