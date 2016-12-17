.SUFFIXES: .c .o .a

-include "depend.inc"

.o.c:
	cc -c $*.c -o $*.o

all:pdbRead CenterCalc SizeCalc MinCalc MaxCalc InfoPrint Witebase CountElements

pdbRead:pdbRead.c
	cc -c $@.c

CenterCalc:pdbCenterCalc.o pdbRead.o lpdbCenterCalc.o
	cc pdb$@.o lpdb$@.o pdbRead.o -o pdb$@

SizeCalc:pdbSizeCalc.o lpdbSizeCalc.o pdbRead.o lpdbCenterCalc.o
	cc pdb$@.o lpdb$@.o pdbRead.o lpdbCenterCalc.o -o pdb$@ -lm

MinCalc:pdbMinCalc.o lpdbMinCalc.o pdbRead.o
	cc pdb$@.o lpdb$@.o pdbRead.o -o pdb$@

MaxCalc:pdbMaxCalc.o lpdbMaxCalc.o pdbRead.o
	cc pdb$@.o lpdb$@.o pdbRead.o -o pdb$@

InfoPrint:pdbInfoPrint.o lpdbInfoPrint.o pdbRead.o
	cc pdb$@.o lpdb$@.o pdbRead.o lpdbCenterCalc.o lpdbSizeCalc.o lpdbMinCalc.o lpdbMaxCalc.o -o pdb$@ -lm

Writebase:pdbWritebase.o lpdbWritebase.o pdbRead.o
	cc pdb$@.o lpdb$@.o pdbRead.o -o pdb$@

CountElements:pdbCountEleents.o lpdbCountElements.o pdbRead.o
	cc pdb$@.o lpdb$@.o pdbRead.o -o pdb$@

test:out3 out4 out5 out6 out7 out9 out10

out3:
	./pdbCenterCalc protein_myosin_5m05.pdb out3.txt

out4:
	./pdbSizeCalc protein_myosin_5m05.pdb out4.txt

out5:
	./pdbMinCalc protein_myosin_5m05.pdb out5.txt

out6:
	./pdbMaxCalc protein_myosin_5m05.pdb out6.txt

out7:
	./pdbInfoPrint protein_myosin_5m05.pdb out7.txt

out9:
	./pdbWritebase protein_myosin_5m05.pdb out9.txt

out10:
	./pdbCountElements protein_myosin_5m05.pdb out10.txt

depend::
	cc -M *.a > depend.inc

clean::
	rm *.o *.a
