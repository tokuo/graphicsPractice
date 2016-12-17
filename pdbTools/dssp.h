#ifndef DSSP_H
#define DSSP_H

#include <stdio.h>

typedef int   dsspIntegerType;
typedef float dsspRealType;

#define DSSP_ONE_RECORD_LEN  (1024)
#define DSSP_RESIDUE_TITLE_LINE "  #  RESIDUE AA STRUCTURE BP1 BP2  ACC"

#define DSSP_SEQRESNUM_START (0)
#define DSSP_SEQRESNUM_LEN   (5)
#define DSSP_RESNUM_START    (DSSP_SEQRESNUM_START+DSSP_SEQRESNUM_LEN)
#define DSSP_RESNUM_LEN      (5)
#define DSSP_CHAINID_START   (DSSP_RESNUM_START+DSSP_RESNUM_LEN+1)
#define DSSP_CHAINID_LEN     (1)
#define DSSP_RESNAME_START   (DSSP_CHAINID_START+DSSP_CHAINID_LEN+1)
#define DSSP_RESNAME_LEN     (1)
#define DSSP_SAS_START       (33)
#define DSSP_SAS_LEN         (5)

typedef struct dsspOneRecordResidue dsspOneRecordResidue;

struct dsspOneRecordResidue {
	dsspIntegerType seqResNumber;
	dsspIntegerType resNumber;
	char            chainID;
	char            resName;
	dsspIntegerType SolventAccessibleSurface;				

	char* unsupportedString;

	dsspOneRecordResidue* next;
	dsspOneRecordResidue* previous;
};

typedef struct dsspFile {
	 dsspOneRecordResidue* top;
	 dsspOneRecordResidue* current;
	 dsspOneRecordResidue* bottom;
} dsspFile;

extern void dsspInit(dsspFile* dssp, int mode);
extern dsspOneRecordResidue* dsspOneRecordResidueAllocate();

extern void dsspFileRead(dsspFile* dssp, FILE* fpt, int mode);
extern void dsspFileOneRecordResidueRead(dsspOneRecordResidue* res, char* s, int mode);

#endif /* DSSP_H */
