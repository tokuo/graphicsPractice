.SUFFIXES: .c .o .a


PDBSOURCE= \
	pdbInit.c \
	pdbUtil.c \
	pdbFile.c \

DSNSOURCE = \
	dsn6Init.c \
	dsn6Write.c 

DSSPSOURCE = \
	dsspInit.c \
	dsspRead.c 

.c.o:
	gcc -g -c -Wall $*.c  -o $*.o

all: pdb2dsn6 dssp2pdb

pdb2dsn6: pdb2dsn6.o lpdb2dsn6.o lib
	cc -o $@ pdb2dsn6.o lpdb2dsn6.o -L./ -lPDB -lDSN6  -lm

dssp2pdb: dssp2pdb.o ldssp2pdb.o lib
	cc -o $@ dssp2pdb.o ldssp2pdb.o -L./ -lPDB -lDSSP  -lm

lib: libPDB.a libDSN6.a libDSSP.a

libPDB.a: $(PDBSOURCE:.c=.o)
	echo $@
	ar r $@ $(PDBSOURCE:.c=.o)

libDSN6.a: $(DSNSOURCE:.c=.o)
	echo $@
	ar r $@ $(DSNSOURCE:.c=.o)

libDSSP.a: $(DSSPSOURCE:.c=.o)
	echo $@
	ar r $@ $(DSSPSOURCE:.c=.o)

depend:
	cc -M *.c > dependency 

clean: 
	rm -f *.o *.a
	rm -f pdb2dsn6 dssp2pdb

include dependency
