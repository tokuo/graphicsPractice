#include"PDB.h"

void bondCADraw(FILE* fpt, arrayPDB pdb){
 fprintf(fpt,"%f\t%f\tmoveto\n",pdb.CA[0].x,pdb.CA[0].y);
 for(int i=1;i<80;i++){
  fprintf(fpt,"%f\t%f\tlineto\n",pdb.CA[i].x,pdb.CA[i].y);
 }
 fprintf(fpt,"stroke\n");
}
