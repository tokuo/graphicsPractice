#include "./pdb.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* __pdbRecord[] = {
	"ATOM  ",
	"HETATM",
	NULL
} ;

pdbRecordType
pdbRecordTypeAssign(char* s)
{
	pdbRecordType tmp;

	for(tmp=0; tmp!=pdbRecordUnsupported; tmp++) {
		if(0==strncmp(s, __pdbRecord[tmp], RECORDNAME_LEN)) {	
			break;
		}
	}
	return tmp;
}

char* 
pdbRecordStringAssign(pdbRecordType record, char* s)
{
	if(record<pdbRecordUnsupported) {
		sprintf(s, __pdbRecord[record]);
	} else {
		fprintf(stderr, "Not supported record: %d\n", record);
		exit(EXIT_FAILURE);
	}
	return s;
}

int
pdbIsAtom(pdbOneRecord* current) 
{
	if(pdbRecordATOM    == current->record 
	 ||pdbRecordHETATM == current->record) {
		return 1;
	} else {
		return 0;
	}
}

int
pdbZValueGet(pdbOneRecord* current)
{
	if(       current->atomName[1] == 'H') {
		return 1;		
	} else if(current->atomName[0] == ' ' && current->atomName[1] == 'C') {
		return 6;		
        } else if(current->atomName[0] == ' ' && current->atomName[1] == 'N') {
		return 7;		
	} else if(current->atomName[0] == ' ' && current->atomName[1] == 'O') {
		return 8;		
	} else if(current->atomName[0] == ' ' && current->atomName[1] == 'P') {
		return 15;	
	} else if(current->atomName[0] == ' ' && current->atomName[1] == 'S') {
		return 16;
	} else if(current->atomName[0] == 'M' && current->atomName[1] == 'G') {
		return 12;
	} else if(current->atomName[0] == 'C' && current->atomName[1] == 'A') {
		return 20;
	} else {
		fprintf(stderr, "Not supported element: %c%c\n", current->atomName[0], current->atomName[1]);
		return 6;
	}
}

void
pdbAreaInfo(pdbFile* pdb, pdbCoord* mean, double* max, int mode)
{
	double tmp;

	pdb->current = pdb->top;
	mean->x = mean->y = mean->z = 0;	
	while(NULL!=pdb->current) {
		if(pdbIsAtom(pdb->current)) {
			mean->x += pdb->current->coord.x;
			mean->y += pdb->current->coord.y;
			mean->z += pdb->current->coord.z;
		}	
		pdb->current = pdb->current->next;
	}

	mean->x /= pdb->nAtom;
	mean->y /= pdb->nAtom;
	mean->z /= pdb->nAtom;


	pdb->current = pdb->top;
	*max = 0;	
	while(NULL!=pdb->current) {
		if(pdbIsAtom(pdb->current)) {
			tmp = sqrt((mean->x - pdb->current->coord.x)*(mean->x - pdb->current->coord.x)
				  +(mean->y - pdb->current->coord.y)*(mean->y - pdb->current->coord.y)
				  +(mean->z - pdb->current->coord.z)*(mean->z - pdb->current->coord.z));
			if(*max<tmp) {
				*max = tmp;
			}
		}	
		pdb->current = pdb->current->next;
	}
} 

