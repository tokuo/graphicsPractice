#include "PDB.h"

void lpdbMinCalc(PDB* pdb){

  pdb->current=pdb->top;
  pdb->min.x=pdb->current->atom.x;
  pdb->min.y=pdb->current->atom.y;
  pdb->min.z=pdb->current->atom.z;

  while(pdb->current->nextAtom!=NULL){
    if(pdb->current->atom.x <pdb->min.x){
      pdb->min.x=pdb->current->atom.x;
    }
    if(pdb->current->atom.y <pdb->min.y){
      pdb->min.y=pdb->current->atom.y;
    }
    if(pdb->current->atom.z <pdb->min.z){
      pdb->min.z=pdb->current->atom.z;
    }
    pdb->current=pdb->current->nextAtom;
  }
}
