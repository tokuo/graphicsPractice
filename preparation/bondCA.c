#include"PDB.h"


void bondCADraw2(FILE* fpt,PDB *pdb){
 pdb->currentCA = pdb->topCA;
 fprintf(fpt,"%! PS-Adobe-3.0\n%f\t%f\tmoveto\n",pdb->currentCA->atom.x,pdb->currentCA->atom.y);
 pdb->currentCA = pdb->currentCA->nextCA;
 for(;pdb->currentCA != NULL;pdb->currentCA = pdb->currentCA->nextCA){
  fprintf(fpt,"%f\t%f\tlineto\n",pdb->currentCA->atom.x,pdb->currentCA->atom.y);
 }
 fprintf(fpt,"stroke\nshowpage\n");
}


void bondCADraw4(FILE* fpt,PDB *pdb,double originx,double originy,double scale){
 pdb->currentCA = pdb->topCA;
 fprintf(fpt,"%! PS-Adobe-3.0\n%f\t%f\tmoveto\n",(pdb->currentCA->atom.x + originx)*scale,(pdb->currentCA->atom.y + originy)*scale);
 pdb->currentCA = pdb->currentCA->nextCA;
 for(;pdb->currentCA != NULL;pdb->currentCA = pdb->currentCA->nextCA){
  fprintf(fpt,"%f\t%f\tlineto\n",(pdb->currentCA->atom.x + originx)*scale,(pdb->currentCA->atom.y + originy)*scale);
 }
 fprintf(fpt,"stroke\nshowpage\n");
}


void bondCADraw(FILE* fpt, arrayPDB pdb){
 fprintf(fpt,"%! PS-Adobe-3.0\n%f\t%f\tmoveto\n",pdb.CA[0].x,pdb.CA[0].y);
 for(int i=1;i<80;i++){
  fprintf(fpt,"%f\t%f\tlineto\n",pdb.CA[i].x,pdb.CA[i].y);
 }
 fprintf(fpt,"stroke\nshowpage\n");
}


void bondCADraw3(FILE* fpt, arrayPDB pdb,double startx,double starty,double scale){
 fprintf(fpt,"%! PS-Adobe-3.0\n%f\t%f\tmoveto\n",(pdb.CA[0].x + startx)*scale,(pdb.CA[0].y + starty)*scale);
 for(int i=1;i<80;i++){
  fprintf(fpt,"%f\t%f\tlineto\n",(pdb.CA[i].x + startx)*scale,(pdb.CA[i].y + starty)*scale);
 }
 fprintf(fpt,"stroke\nshowpage\n");
}
