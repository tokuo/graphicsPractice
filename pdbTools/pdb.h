#ifndef PDB_H
#define PDB_H

#include <stdio.h>

typedef float pdbRealType;
typedef int   pdbIntegerType;

typedef enum pdbRecordType {
	pdbRecordATOM=0,
	pdbRecordHETATM,
	pdbRecordUnsupported
} pdbRecordType;

#define RECORD_LEN       (80)

#define RECORDNAME_START (0)
#define RECORDNAME_LEN   (6)
#define SERIAL_START     (RECORDNAME_START+RECORDNAME_LEN)
#define SERIAL_LEN       (5)
#define ATOMNAME_START   (SERIAL_START+SERIAL_LEN+1)
#define ATOMNAME_LEN     (4)
#define ALTLOC_START     (ATOMNAME_START+ATOMNAME_LEN)
#define ALTLOC_LEN       (1)
#define RESNAME_START    (ALTLOC_START+ALTLOC_LEN)
#define RESNAME_LEN      (3)
#define CHAINID_START    (RESNAME_START+RESNAME_LEN+1)
#define CHAINID_LEN      (1)
#define RESSEQ_START     (CHAINID_START+CHAINID_LEN)
#define RESSEQ_LEN       (4)
#define ICODE_START      (RESSEQ_START+RESSEQ_LEN)
#define ICODE_LEN        (1)
#define COORDX_START     (ICODE_START+ICODE_LEN+3)
#define COORDX_LEN       (8)
#define COORDY_START     (COORDX_START+COORDX_LEN)
#define COORDY_LEN       (8)
#define COORDZ_START     (COORDY_START+COORDY_LEN)
#define COORDZ_LEN       (8)
#define OCCUPANCY_START  (COORDZ_START+COORDZ_LEN)
#define OCCUPANCY_LEN    (6)
#define TEMPFACTOR_START (OCCUPANCY_START+OCCUPANCY_LEN)
#define TEMPFACTOR_LEN   (6)
#define SEGID_START      (TEMPFACTOR_START+TEMPFACTOR_LEN+6)
#define SEGID_LEN        (4)
#define ELEMENT_START    (SEGID_START+SEGID_LEN)
#define ELEMENT_LEN      (2)
#define CHARGE_START     (ELEMENT_START+ELEMENT_LEN)
#define CHARGE_LEN       (2)


#define ATOM_RECORD_FORMAT    "%6s%5d %4s%c%3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f      %4s%2s%2s"
#define GENERAL_RECORD_FORMAT "%80s"


typedef struct pdbCoord {
	pdbRealType x;
	pdbRealType y;
	pdbRealType z;
} pdbCoord;

typedef struct pdbOneRecord pdbOneRecord;

struct pdbOneRecord {
	pdbRecordType   record;
	pdbIntegerType  atomSerialNumber;
	char atomName[4+1];
	char altLoc;
	char resName[3+1];
	char chainID;
	pdbIntegerType  resSequenceNumber;
	char iCode;
	pdbCoord 	coord;
	pdbRealType	occupancy;
	pdbRealType	tempFactor;
	char		segID[4+1];
	char		element[2+1];
	char 		charge[2+1];

	char*		unsupportedRecord;

	pdbOneRecord* next;	
	pdbOneRecord* previous;
} ;

typedef struct pdbFile {
	pdbOneRecord* top;
	pdbOneRecord* current;
	pdbOneRecord* bottom;
	pdbIntegerType nAtom;
} pdbFile;

extern void pdbFileRead(pdbFile* pdb, FILE* fpt, int mode);
extern void pdbFileOneRecordRead(pdbOneRecord* current, char* s, int mode);
extern void pdbFileWrite(pdbFile* pdb, FILE* fpt, int mode);
extern void pdbFileOneRecordWrite(pdbOneRecord* current, char* s, int mode);
extern void pdbInit(pdbFile* pdb, int mode);
extern pdbOneRecord* pdbOneRecordAllocate();
extern int pdbIsAtom(pdbOneRecord* current);
extern pdbRecordType pdbRecordTypeAssign(char* s);
extern char* pdbRecordStringAssign(pdbRecordType record, char* s);
extern int pdbZValueGet(pdbOneRecord* pdb);
extern void pdbAreaInfo(pdbFile* pdb, pdbCoord* mean, double* max, int mode);


#endif /* PDB_H */

