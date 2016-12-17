#include"PDB.h"

void bondDraw(FILE* fpt, float startx, float starty, float endx, float endy){
 fprintf(fpt,"%! PS-Adobe-3.0\n%f %f moveto\n%f %f ineto\nstroke\nshowpage\n",startx,starty,endx,endy);
}
