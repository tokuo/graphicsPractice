#include"PDB.h"

void arrayPDBRead(FILE* fpt, arrayPDB *pdb){
 int a=0,b=0;
 char readLine[80];
 char check1[] = "Atom";
 char check2[] = "CA";
 char *c,*c2,*c3,*c4;
 int i,i2;
 double f1,f2,f3;
 double x,y,z;
 while(fgets(readLine,256,fpt)!=NULL){
  puts(readLine);
  if(strstr(readLine,check1)!=NULL){
   a++;
   if(strstr(readLine,check2)!=NULL){
    b++;
   }
  }
 }
 pdb->numAtom = a;
 pdb->numCAAtom = b;
 fseek(fpt,0L,SEEK_SET);
 pdb->CA = (Atom *)malloc(sizeof(Atom)*pdb->numCAAtom);
 a = 0;
 while(fgets(readLine,80,fpt)!=NULL){
  if(strstr(readLine,check1)!=NULL){
   if(strstr(readLine,check2)!=NULL){
    fseek(fpt,-1L,SEEK_SET);
    fscanf(fpt,"%s %d %s %s %d %lf %lf %lf %lf %lf %s %lf",c,&i,c2,c3,&i2,&x,&y,&z,&f1,&f2,c4,&f3);
    pdb->CA[a].x = x;
    pdb->CA[a].y = y;
   }
  }
  a++;
 }
}
