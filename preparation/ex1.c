#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void bondDraw(FILE* fpt, float startx, float starty, float endx, float endy){
 fprintf(fpt,"%! PS-Adobe-3.0\n%f %f moveto\n%f %f ineto\nstroke\nshowpage\n",startx,starty,endx,endy);
}

int main(int argc,char *argv[]){
 FILE *f;

 if((f=fopen(argv[1],"w"))==NULL){
  printf("error\n");
  exit(1);
 }

 bondDraw(f,atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]));

 return 0;
}
