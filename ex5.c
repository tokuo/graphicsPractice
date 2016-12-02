#include"PDB.h"

int main(int argc,char *argv[]){
 FILE *f1,*f2;
 arrayPDB pdb;

 if((f1=fopen(argv[1],"r"))==NULL){
  printf("error\n");
  exit(1);
 }

 if((f2=fopen(argv[2],"w"))==NULL){
  printf("error\n");
  exit(1);
 }
 
  pdbRead(f1,&pdb);
  bondCADraw2(f2,&pdb);
  
 return 0;
}
