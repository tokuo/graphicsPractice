#include <stdio.h>
#include <string.h>
#include "./ldssp2pdb.h"

void
ldssp2pdb(dsspFile* dssp, pdbFile* pdb, pdbFile* out, ldssp2pdbInfo linfo, int mode) 
{
	pdbOneRecord* tmp;

	out->top = out->bottom = out->current = NULL;

	pdb->current = pdb->top;
	while(NULL!=pdb->current) {
		if(NULL==out->current) {
			out->top = pdbOneRecordAllocate();
			tmp = NULL;
			out->current = out->top;
		} else {
			out->current->next = pdbOneRecordAllocate();
			tmp = out->current;
			out->current = out->current->next;
		}
		out->bottom  = out->current;
		*(out->current) = *(pdb->current); 
		out->current->next = NULL;
		out->current->previous = tmp;

		if(pdbIsAtom(out->current)) {
			dssp->current = dssp->top;
			while(NULL!=dssp->current) {
				if(dssp->current->resNumber == out->current->resSequenceNumber
			 	 &&dssp->current->chainID   == pdb->current->chainID) {
					out->current->tempFactor = (float)dssp->current->SolventAccessibleSurface;
					break;
				} 

				dssp->current = dssp->current->next;					
			}
		} else {
			out->current->unsupportedRecord = strdup(pdb->current->unsupportedRecord);
		}

		pdb->current = pdb->current->next;
	}
}


