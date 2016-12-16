#include<stdio.h>
#include<string.h>
#include "PDB.h"

void numElements(PDB*pdb) {

  int i, ne[] = {0, 0, 0, 0, 0, 0};
  char pse[6][2] = {"C", "H", "N", "O", "P", "X"};
  
  for(pdb->current = pdb->top; pdb->current != NULL; pdb->current->nextAtom) {
    for(i = 0; i < 5; i++) {
      if(strcmp(pdb->current->atom.element, pse[i]) == 0) {
	ne[i]++;
	break;
      }
    }
    if(i == 5) ne[5]++;
  }

  for(i = 0; i < 6; i++) {
    printf("%s:\t%d\n", pse[i], ne[i]);
  }
}
