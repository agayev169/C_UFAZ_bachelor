#-------------
#Using makefile 
#-------------
# $@ target
# $^ components
# $< the first component
# MACROS ;; SOURCES= LL.c Stack.c main.c

SOURCES=$(wildcard *.c)
EXEC=project

$(EXEC) : $(SOURCES)
	gcc $^ -o $@ -lm

clean :
	rm $(EXEC)
