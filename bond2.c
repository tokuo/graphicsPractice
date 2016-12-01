#include"PDB.h"

void bondDraw2(FILE* fpt, Bond l){
 fprintf(fpt,"%! PS-Adobe-3.0\n%f %f moveto\n%f %f ineto\nstroke\nshowpage\n",l.start.x,l.start.y,l.end.x,l.end.y);
}
