

CC=gcc

########################
# Détection de l'OS
#########################

OS = $(shell uname)


CFLAGS= -g -O0 -Wall \
		-I. -I /usr/include \
		-I /usr/local/include \
		-I /opt/X11/include

ifeq (${OS},Darwin)
  CFLAGS := ${CFLAGS} -I /System/Library/Frameworks/OpenGL.framework/Headers
else
  CFLAGS := ${CFLAGS} -I /usr/include/GL
endif

CCOPTIONS = -g -O0 -Wall


ifeq ($(OS),Darwin)
	LIBS = -lm -framework OpenGL -framework GLUT
else
	LIBS = -lm -lGLU -lGL -lglut
endif

EXEC=plot
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

$(EXEC) : $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) -c $^ -o $@ $(CFLAGS)

clean :
	/bin/rm $(EXEC) *.o
