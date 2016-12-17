#include "PDB.h"

void lpdbMaxCalc(PDB* pdb){

  pdb->current=pdb->top;
  pdb->max.x=pdb->current->atom.x;
  pdb->max.y=pdb->current->atom.y;
  pdb->max.z=pdb->current->atom.z;

  while(pdb->current->nextAtom!=NULL){
    if(pdb->current->atom.x > pdb->max.x){
      pdb->max.x=pdb->current->atom.x;
    }
    if(pdb->current->atom.y > pdb->max.y){
      pdb->max.y=pdb->current->atom.y;
    }
    if(pdb->current->atom.z > pdb->max.z){
      pdb->max.z=pdb->current->atom.z;
    }
    pdb->current=pdb->current->nextAtom;
  }
}
