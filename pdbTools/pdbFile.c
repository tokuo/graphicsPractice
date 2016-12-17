#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./pdb.h"

void
pdbFileRead(pdbFile* pdb, FILE* fpt, int mode)
{
	char s[RECORD_LEN+3];

	pdbInit(pdb, mode);

	while(NULL!=fgets(s, RECORD_LEN+2, fpt)) {
		s[RECORD_LEN] = '\0';
		if(NULL==pdb->top) {
			pdb->top = pdbOneRecordAllocate();
			pdb->current = pdb->top;
			pdb->current->previous = NULL;
		} else {
			pdb->current->next = pdbOneRecordAllocate();
			pdb->current->next->previous = pdb->current;
			pdb->current = pdb->current->next;
		}
		pdb->bottom = pdb->current;
		pdb->current->next = NULL;
		pdbFileOneRecordRead(pdb->current, s, mode);
		if(pdbIsAtom(pdb->current)) {
			pdb->nAtom++;
		}
	}
}

void
pdbFileOneRecordRead(pdbOneRecord* current, char* s, int mode)
{
	char stmp[RECORD_LEN+2];
	
	stmp[RECORDNAME_LEN] = 0;
	current->record = pdbRecordTypeAssign(strncpy(stmp, s+RECORDNAME_START, RECORDNAME_LEN));

	if(pdbIsAtom(current)) {
		stmp[SERIAL_LEN] = 0;
		current->atomSerialNumber = atoi(strncpy(stmp, s+SERIAL_START, SERIAL_LEN));
		current->atomName[ATOMNAME_LEN];
		strncpy(current->atomName, s+ATOMNAME_START, ATOMNAME_LEN);
		current->altLoc = s[ALTLOC_START];
		current->resName[RESNAME_LEN];
		strncpy(current->resName, s+RESNAME_START, RESNAME_LEN);
		current->chainID = s[CHAINID_START];
		stmp[RESSEQ_LEN] = 0;
		current->resSequenceNumber = atoi(strncpy(stmp, s+RESSEQ_START, RESSEQ_LEN));
		current->iCode = s[ICODE_START];
		stmp[COORDX_LEN] = 0;
		current->coord.x = (float)atof(strncpy(stmp, s+COORDX_START, COORDX_LEN));
		stmp[COORDY_LEN] = 0;
		current->coord.y = (float)atof(strncpy(stmp, s+COORDY_START, COORDY_LEN));
		stmp[COORDZ_LEN] = 0;
		current->coord.z = (float)atof(strncpy(stmp, s+COORDZ_START, COORDZ_LEN));
		stmp[OCCUPANCY_LEN] = 0;
		current->occupancy = (float)atof(strncpy(stmp, s+OCCUPANCY_START, OCCUPANCY_LEN));
		stmp[TEMPFACTOR_LEN] = 0;
		current->tempFactor = (float)atof(strncpy(stmp, s+TEMPFACTOR_START, TEMPFACTOR_LEN));
		current->segID[SEGID_LEN] = 0;
		strncpy(current->segID, s+SEGID_START, SEGID_LEN);
		current->element[ELEMENT_LEN] = 0;
		strncpy(current->element, s+ELEMENT_START, ELEMENT_LEN);
		current->charge[CHARGE_LEN] = 0;
		strncpy(current->charge, s+CHARGE_START, CHARGE_LEN);				
#ifdef DEBUG
		pdbFileOneRecordWrite(current, stmp, 0);
		fprintf(stdout,  GENERAL_RECORD_FORMAT, stmp);
#endif

	} else {
		current->unsupportedRecord = strdup(s);
	}
}


void
pdbFileWrite(pdbFile* pdb, FILE* fpt, int mode)
{
	char s[RECORD_LEN+2];

	pdb->current = pdb->top;
	while(NULL!=pdb->current) {
		pdbFileOneRecordWrite(pdb->current, s, mode);
		fprintf(fpt, GENERAL_RECORD_FORMAT, s);
		fprintf(fpt, "\n");
		pdb->current = pdb->current->next;
	}
}

void
pdbFileOneRecordWrite(pdbOneRecord* current, char* s, int mode)
{
	char stmp[RECORD_LEN+2];

	if(pdbIsAtom(current)) {
		sprintf(s, ATOM_RECORD_FORMAT, 
			pdbRecordStringAssign(current->record, stmp),
			current->atomSerialNumber,
			current->atomName,
			current->altLoc,
			current->resName,
			current->chainID,
			current->resSequenceNumber,
			current->iCode,
			current->coord.x,
			current->coord.y,
			current->coord.z,
			current->occupancy,
			current->tempFactor,
			current->segID,
			current->element,
			current->charge);		
	} else {
		sprintf(s, GENERAL_RECORD_FORMAT, current->unsupportedRecord);
	}		
}
