#include "./dssp.h"

#include <stdlib.h>
#include <string.h>

void
dsspFileRead(dsspFile* dssp, FILE* fpt, int mode)
{
	char s[DSSP_ONE_RECORD_LEN];	
	int  flagRes = 0;	

	dsspInit(dssp, 0);
	while(NULL!=fgets(s, DSSP_ONE_RECORD_LEN-1, fpt)) {
		if(0==flagRes) {
			if(s==strstr(s, DSSP_RESIDUE_TITLE_LINE)) {
				flagRes=1;	
			}
		} else {
			//fprintf(stderr, "%s\n", s);
			if(NULL==dssp->top) {
				dssp->top = dsspOneRecordResidueAllocate();
				dssp->current = dssp->top;
				dssp->current->previous = NULL;
			} else {
				dssp->current->next =  dsspOneRecordResidueAllocate();	
				dssp->current->next->previous = dssp->current;
				dssp->current = dssp->current->next;
			}
			dssp->current->next = NULL;
			dssp->bottom = dssp->current;
	
			dsspFileOneRecordResidueRead(dssp->current, s, mode);
		}
	} 
}

void
dsspFileOneRecordResidueRead(dsspOneRecordResidue* res, char* s, int mode)
{
	char stmp[DSSP_ONE_RECORD_LEN];	

	stmp[DSSP_SEQRESNUM_LEN] = 0; 
	res->seqResNumber = atoi(strncpy(stmp, s+DSSP_SEQRESNUM_START, DSSP_SEQRESNUM_LEN));  	
	stmp[DSSP_RESNUM_LEN] = 0;
	res->resNumber    = atoi(strncpy(stmp, s+DSSP_RESNUM_START, DSSP_RESNUM_LEN));  	
	res->chainID      = s[DSSP_CHAINID_START];
	res->resName      = s[DSSP_RESNAME_START];
	stmp[DSSP_SAS_LEN];
	res->SolventAccessibleSurface = atoi(strncpy(stmp, s+DSSP_SAS_START, DSSP_SAS_LEN));
	//fprintf(stderr, "%d %d %c %d = %s\n", res->seqResNumber, res->resNumber, res->chainID, res->SolventAccessibleSurface, stmp);
}

