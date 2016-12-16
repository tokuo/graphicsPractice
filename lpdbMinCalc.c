#include<stdio.h>
#include "PDB.h"

void min(PDB* pdb){

  pdb->current=pdb->bottom;
  pdb->min.x=pdb->cyrrent->atom.x;
  pdb->min.y=pdb->cyrrent->atom.y;
  pdb->min.z=pdb->cyrrent->atom.z;

  while(pdb->current->nextArom!=NULL){
    pdb->current=pdb->current->nextAtom;
    if(pdb->current->atom.x <pdb->min.x){
      pdb->min.x=pdb->current->atom.x;
    }
    if(pdb->current->atom.y <pdb->min.y){
      pdb->min.y=pdb->current->atom.y;
    }
    if(pdb->current->atom.z <pdb->min.z){
      pdb->min.z=pdb->current->atom.z;
    }
  }
}
