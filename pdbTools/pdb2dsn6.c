#include <stdio.h>
#include <stdlib.h>
#include "./pdb.h"
#include "./DSN6.h"
#include "./pdb2dsn6.h"


int 
main(int argc, char* argv[])
{
	FILE* fptIn;
	FILE* fptOut;
	lpdb2dsn6Info linfo;
	pdbFile pdb;
	Dsn6    map;
	
	/* Argument Check */	
	if(argc!=4) {
		fprintf(stderr, "%s pdbFileName densityDSNFileName SamplingRate[A]\n", argv[0]);
		exit(EXIT_FAILURE);
	}	

	fptIn = fopen(argv[1], "r");
	if(NULL==fptIn) {
		fprintf(stderr, "FileNotOpened: %s\n", argv[1]);	
		exit(EXIT_FAILURE);
	}

	fptOut = fopen(argv[2], "w");
	if(NULL==fptOut) {
		fprintf(stderr, "FileNotOpend: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	linfo.SamplingRate = atof(argv[3]);

	/* pdbFile Read */
	pdbFileRead(&pdb, fptIn, 0);

	/* Atomic model to density */	
	lpdb2dsn6(&pdb, &map, linfo, 0);
	
	/* DensityFile Write */
	dsn6FileWrite(&map, fptOut, 0);	
	return 0;
}


