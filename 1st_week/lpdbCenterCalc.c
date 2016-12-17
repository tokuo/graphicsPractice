#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include"PDB.h"

void lpdbCenterCalc(PDB* pdb){
  pdb->Center.x=0;
  pdb->Center.y=0;
  pdb->Center.z=0;

  for(pdb->current=pdb->top;pdb->current !=NULL;pdb->current=pdb->current->nextAtom){
    pdb->Center.x+=pdb->current->atom.x;
    pdb->Center.y+=pdb->current->atom.y;
    pdb->Center.z+=pdb->current->atom.z;
  }
  pdb->Center.x=pdb->Center.x/numAtom;
  pdb->Center.y=pdb->Center.y/numAtom;
  pdb->Center.z=pdb->Center.z/numAtom;

}
