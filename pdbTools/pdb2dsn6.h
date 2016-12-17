#ifndef PDB_DENSITY_H
#define PDB_DENSITY_H

#include "pdb.h"

typedef struct lpdb2dsn6Info {
	pdbRealType SamplingRate;		
} lpdb2dsn6Info;

extern void lpdb2dsn6(pdbFile* pdb, Dsn6* map, lpdb2dsn6Info linfo, int mode);
#endif /*  PDB_DENSITY_H */
