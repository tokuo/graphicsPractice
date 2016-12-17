#include "PDB.h"

int main(int argc, char*argv[]) {

  char *pdbfn, *outputfn;
  FILE *fpt;
  PDB pdb;

  if(argc != 3) {
    printf("error: Argument is invalid\n");
    exit(EXIT_FAILURE);

  } else {
    pdbfn = argv[1];
    outputfn = argv[2];
  }
  
  if((fpt = fopen(pdbfn, "r")) == NULL) {
    printf("error: %s is not opened\n", pdbfn);
    exit(EXIT_FAILURE);
  }

  pdbRead(fpt, &pdb);
  fclose(fpt);
  lpdbCenterCalc(&pdb);
  lpdbSizeCalc(&pdb);

  if((fpt = fopen(outputfn, "w")) == NULL) {
    printf("error: %s is not opened\n", outputfn);
    exit(EXIT_FAILURE);
  }

  fprintf(fpt, "maxRadius: %f", pdb.maxRadius);
  fclose(fpt);

  

  return 0;

}
