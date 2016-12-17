#include <stdio.h>
#include <stdlib.h>
#include "./pdb.h"

void
pdbInit(pdbFile* pdb, int mode)
{
	pdb->nAtom = 0;
	pdb->top = pdb->bottom = pdb->current = NULL;
}

pdbOneRecord*
pdbOneRecordAllocate()
{
	pdbOneRecord* ptr;

	ptr = (pdbOneRecord*)malloc(sizeof(pdbOneRecord));
	if(NULL==ptr) {
		fprintf(stderr, "Cannot allocate atomRecord\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
