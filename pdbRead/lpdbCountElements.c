#include "PDB.h"

void lpdbCountElements(FILE* fpt,PDB* pdb) {

  int i, ne[6] = {0, 0, 0, 0, 0, 0};
  char pse[7] = "CHNOPX";
  
  for(pdb->current = pdb->top; pdb->current != NULL; pdb->current = pdb->current->nextAtom) {
    for(i = 0; i < 5; i++) {
      if(pdb->current->atom.element[0] == pse[i]) {
	ne[i]++;
	break;
      }
      if(i == 5) ne[5]++;
    }
  }

  for(i = 0; i < 6; i++) {
    fprintf(fpt,"%c:\t%d\n", pse[i], ne[i]);
  }
}
