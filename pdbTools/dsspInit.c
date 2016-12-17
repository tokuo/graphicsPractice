#include "./dssp.h"

#include <stdio.h>
#include <stdlib.h>

void
dsspInit(dsspFile* dssp, int mode)
{
	dssp->top = dssp->bottom = dssp->current = NULL;
}

dsspOneRecordResidue* 
dsspOneRecordResidueAllocate()
{
	dsspOneRecordResidue* tmp;

	tmp = (dsspOneRecordResidue*)malloc(sizeof(dsspOneRecordResidue));
	if(NULL==tmp) {
		fprintf(stderr, "Memory not allocated in dsspOneRecordResidueAllocate\n");
		exit(EXIT_FAILURE);
	}
	return tmp;
}
