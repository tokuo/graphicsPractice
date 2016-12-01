#include"PDB.h"

int main(int argc,char *argv[]){
 FILE *f;
 Bond in;
 in.start.x = atof(argv[2]);
 in.start.y = atof(argv[3]);
 in.end.x = atof(argv[4]);
 in.end.y = atof(argv[5]);

 if((f=fopen(argv[1],"w"))==NULL){
  printf("error\n");
  exit(1);
 }

  bondDraw2(f,in);

 return 0;
}
