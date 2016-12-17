#include"PDB.h"

int main(int argc,char *argv[]){
 FILE *f;

 if((f=fopen(argv[1],"w"))==NULL){
  printf("error\n");
  exit(1);
 }

 bondDraw(f,atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]));

 return 0;
}
