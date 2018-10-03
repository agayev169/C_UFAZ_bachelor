#-------------
#Using makefile 
#-------------
# $@ target
# $^ components
# $< the first component
# MACROS ;; SOURCES= LL.c Stack.c main.c

SOURCES_COMPRESS = main.c LL.c HT.c
EXEC_COMPRESS = compress

SOURCES_DECOMPRESS = decompress.c HuffChar.h HuffChar.c
EXEC_DECOMPRESS = decompress

$(EXEC_COMPRESS): $(SOURCES_COMPRESS)
	gcc $^ -o $@ -lm
	
$(EXEC_DECOMPRESS): $(SOURCES_DECOMPRESS)
	gcc $^ -o $@ -lm

clean:
	rm $(EXEC_COMPRESS) $(EXEC_DECOMPRESS)
