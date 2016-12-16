#include<stdio.h>
#include<math.h>
#include "PDB.h"

void lpdbSizeCalc(PDB*pdb){
  float radius;

  pdb->maxRadius = sqrt(pow(pdb->top->atom.x-pdb->Center.x,2.0)+pow(pdb->top->atom.y-pdb->Center.y,2.0)+pow(pdb->top->atom.z-pdb->Center.z,2.0));
  for(pdb->current = pdb->top->nextAtom; pdb->current != NULL; pdb->current = pdb->current->nextAtom){
    radius = sqrt(pow(pdb->current->atom.x-pdb->Center.x,2.0)+pow(pdb->current->atom.y-pdb->Center.y,2.0)+pow(pdb->current->atom.z-pdb->Center.z,2.0));
    if(radius > pdb->maxRadius)
      pdb->maxRadius = radius;
  }
}
