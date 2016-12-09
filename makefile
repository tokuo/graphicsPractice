.SUFFIXES: .c .o .a

-include "depend.inc"

SOURCE=bond.c bond2.c

SOURCE2=pdbRead.c bondCA.c

.o.c:
	cc -c $*.c -o $*.o

all:ex1 ex2 ex3 ex4 ex5

ex1: ex1.o
	cc $@.o -o $@ -lm

ex2: ex2.o bond.o
	cc $@.o bond.o -o $@ -lm

ex3: ex3.o libBond.a
	cc $@.o -o $@ -lm -L./ -lBond

ex4:ex4.o libPDB.a
	cc $@.o -o $@ -L./ -lPDB

ex5:ex5.o libPDB.a
	cc $@.o -o $@ -L./ -lPDB

libBond.a: $(SOURCE: .c=.o)
	ar rv $@ bond.o bond2.o

libPDB.a: $(SOURCE2: .c=.o)
	ar rv $@ pdbRead.o bondCA.o

test: test-ex1 test-ex2 test-ex3 test-ex4 test-ex5

test-ex1:
	./ex1 ex1.txt 0 0 10 20

test-ex2:
	./ex2 ex2.txt 10 20 30 40

test-ex3:
	./ex3 ex3.txt 10 20 30 40

test-ex4:
	./ex4 121p-GC.pdb ex4.txt

test-ex5:
	./ex5 121p-GC.pdb ex5.txt

depend::
	cc-M *.a > depend.inc

clean::
	rm *.o *.a ex1 ex2 ex3 ex4 ex5
