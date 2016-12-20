.SUFFIXES: .c .o .a .exe 

LIBS=-lGL -lGLU -lglut -lm 
#LIBS=-framework GLUT -framework OpenGL -lm -L./ -lmyGUI
OBJS=glut_my_key.c glut_my_mouse.c

.c.o:
	gcc -g -Wall -c $*.c -o $*.o 

#gcc -g -Wall -DWIN32 -c $*.c -o $*.o -Wno-deprecated 
#gcc -g -Wall -DWIN32 -c $*.c -o $*.o 

.o.exe:
	gcc -g -Wall -o $*.exe $*.o  -lglut32 -lglu32 -lopengl32 -lm

all: glut_sample glut_sample2 glut_sample3 glut_sample4 glut_sample5

glut_sample: glut_sample.o
	gcc -g -Wall -o $@ $@.o $(LIBS) 
	
glut_sample2: glut_sample2.o
	gcc -g -Wall -o $@ $@.o $(LIBS) 
	
glut_sample3: glut_sample3.o
	gcc -g -Wall -o $@ $@.o $(LIBS) 
	
glut_sample4: glut_sample4.o libmyGUI.a
	gcc -g -Wall -o $@ $@.o $(LIBS) -L./ -lmyGUI  

glut_sample5: glut_sample5.o libmyGUI.a
	gcc -g -Wall -o $@ $@.o $(LIBS) -L./ -lmyGUI

libmyGUI.a: $(OBJS:.c=.o)
	ar r $@ $(OBJS:.c=.o) 

clean:
	rm -rf *.o  *.a *.exe glut_sample glut_sample2 glut_sample3 glut_sample4

include dependency

depend: $(SOURCE)
	gcc -M *.c > dependency
