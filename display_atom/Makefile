.SUFFIXES: .c .o .a 

LIBS=-lGL -lGLU -lglut -lm
#LIBS=-framework GLUT -framework OpenGL -lm
#LIBS=-lglut32 -lglu32 -lopengl32 -DWIN32 -lm

SOURCE= myInit.c myLight.c myIdle.c myCamera.c myKeyboard.c myMouse.c myReshape.c myDisplay.c pdbRead.c	

.c.o:
	gcc -g -Wall -c $*.c -o $*.o

all: red-bull

red-bull: red-bull.o libRed_bull.a
	gcc -g -Wall -o $@ red-bull.o -lm -L./ -lRed_bull $(LIBS)

libRed_bull.a: $(SOURCE:.c=.o)
	ar r $@ $(SOURCE:.c=.o)

test:
	./red-bull

clean:
	rm -rf *.o *.a red-bull

depend: $(SOURCE)
	gcc -M *.c > dependency

-include "dependency"
