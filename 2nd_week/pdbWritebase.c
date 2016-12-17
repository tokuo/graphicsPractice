#include"PDB.h"

int main(int argc,char* argv[]){
  PDB pdb;
  FILE* fpr;
  FILE* fpw;
  if(argc!=3){
    printf("begin error\n");
    exit(1);
  }
  if((fpr=fopen(argv[1],"r"))==NULL){
    printf("read error\n");
    exit(1);
  }
  pdbRead(fpr,&pdb);
  fclose(fpr);
  if((fpw=fopen(argv[2],"w"))==NULL){
    printf("write error\n");
    exit(1);
  }
  lpdbWritebase(fpw,&pdb);
  fclose(fpw);
  return 0;
}
