#include"PDB.h"


void bondCADraw2(FILE* fpt,PDB *pdb){
 pdb->currentCA = pdb->topCA;
 fprintf(fpt,"%f\t%f\tmoveto\n",pdb->currentCA->atom.x,pdb->currentCA->atom.y);
 pdb->currentCA = pdb->currentCA->nextCA;
 for(;pdb->currentCA != NULL;pdb->currentCA = pdb->currentCA->nextCA){
  fprintf(fpt,"%f\t%f\tlineto\n",pdb->currentCA->atom.x,pdb->currentCA->atom.y);
 }
 fprintf(fpt,"stroke\n");
}


void bondCADraw(FILE* fpt, arrayPDB pdb){
 fprintf(fpt,"%f\t%f\tmoveto\n",pdb.CA[0].x,pdb.CA[0].y);
 for(int i=1;i<80;i++){
  fprintf(fpt,"%f\t%f\tlineto\n",pdb.CA[i].x,pdb.CA[i].y);
 }
 fprintf(fpt,"stroke\n");
}
