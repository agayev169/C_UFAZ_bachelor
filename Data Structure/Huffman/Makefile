#-------------
#Using makefile 
#-------------
# $@ target
# $^ components
# $< the first component
# MACROS ;; SOURCES= LL.c Stack.c main.c

SOURCES=$(wildcard *.c)
EXEC=run

$(EXEC) : $(SOURCES)
	gcc $^ -o $@ -lm

clean :
	rm $(SOURCES) $(EXEC)
