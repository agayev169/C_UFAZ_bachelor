MAIN_SOURCES=main.c lifo.c
TEST_SOURCES=test.c lifo.c
MAIN_OBJECTS=$(MAIN_SOURCES:.c=.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)

all:main test

main:$(MAIN_SOURCES) lifo.h
	gcc $(MAIN_SOURCES) -g -Wall -lcunit -o $@

test:$(TEST_SOURCES) lifo.h
	gcc $(TEST_SOURCES) -g -Wall -lcunit -o $@

clean:
	rm main test