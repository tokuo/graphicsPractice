#include<stdio.h>
#include "PDB.h"

void max(PDB* pdb){

  pdb->current=pdb->top;
  pdb->max.x=pdb->cyrrent->atom.x;
  pdb->max.y=pdb->cyrrent->atom.y;
  pdb->max.z=pdb->cyrrent->atom.z;

  while(pdb->current->nextArom!=NULL){
    pdb->current=pdb->current->nextAtom;
    if(pdb->current->atom.x >pdb->min.x){
      pdb->max.x=pdb->current->atom.x;
    }
    if(pdb->current->atom.y >pdb->min.y){
      pdb->max.y=pdb->current->atom.y;
    }
    if(pdb->current->atom.z >pdb->min.z){
      pdb->max.z=pdb->current->atom.z;
    }
  }
}
