#ifndef LDSSP2PDB_H
#define LDSSP2PDB_H
#include "dssp.h"
#include "pdb.h"

typedef struct ldssp2pdbInfo {
	int dummy;
} ldssp2pdbInfo;

extern void ldssp2pdb(dsspFile* dssp, pdbFile* pdb, pdbFile* out, ldssp2pdbInfo linfo, int mode);

#endif /* LDSSP2PDB_H */
