#include<ctype.h>
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
  pdb->Center.x=pdb->Center.x/pdb->numAtom;
  pdb->Center.y=pdb->Center.y/pdb->numAtom;
  pdb->Center.z=pdb->Center.z/pdb->numAtom;

}
