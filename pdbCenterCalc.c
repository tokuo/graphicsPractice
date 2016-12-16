#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include"PDB.h"

int main(int argc,char* argv[]){
  int correct;
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
  correct=pdbRead(fpr,&pdb);
  if(correct!=0){
    printf("nothing in PDB file\n");
    exit(1);
  }
  fclose(fpr);
  if((fpw=fopen(argv[2],"w"))==NULL){
    printf("write error\n");
    exit(1);
  }
  lpdbCenterCalc(&pdb);
  fprintf(fpw,"center %8.3f %8.3f %8.3f\n"pdb->Center.x,pdb->Center.y,pdb->Center.z);
  fclose(fpw);
  return 0;
}
