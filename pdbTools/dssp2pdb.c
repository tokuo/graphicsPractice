#include <stdio.h>
#include <stdlib.h>
#include "./pdb.h"
#include "./dssp.h"
#include "./ldssp2pdb.h"

int
main(int argc, char* argv[])
{
	FILE* fptInPDB;
	FILE* fptInDSSP;
	FILE* fptOutPDB;

	dsspFile dsspIn;
	pdbFile pdbIn;
	pdbFile pdbOut;

	ldssp2pdbInfo linfo;
	
	if(argc!=4) {
		fprintf(stderr, "%s inputDSSP inputPDB outputPDB\n", argv[0]);
		exit(EXIT_FAILURE);
	}			

        fptInDSSP = fopen(argv[1], "r");
        if(NULL==fptInDSSP) {
                fprintf(stderr, "FileNotOpened: %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        fptInPDB = fopen(argv[2], "r");
        if(NULL==fptInPDB) {
                fprintf(stderr, "FileNotOpend: %s\n", argv[2]);
                exit(EXIT_FAILURE);
        }

        fptOutPDB = fopen(argv[3], "w");
        if(NULL==fptOutPDB) {
                fprintf(stderr, "FileNotOpend: %s\n", argv[3]);
                exit(EXIT_FAILURE);
        }

	dsspFileRead(&dsspIn, fptInDSSP, 0);
	pdbFileRead(&pdbIn, fptInPDB, 0); 

	ldssp2pdb(&dsspIn, &pdbIn, &pdbOut, linfo, 0); 
		
	pdbFileWrite(&pdbOut, fptOutPDB, 0);
	return 0;

}



