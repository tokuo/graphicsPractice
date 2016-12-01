#include"PDB.h"
void arrayPDBRead(FILE* fpt, arrayPDB *pdb){
 int a=0,b=0;
 char readLine[80];
 char check1[] = "ATOM";
 char check2[] = "CA";
 char cx[8],cy[8],cz[8];
 while(fgets(readLine,256,fpt)!=NULL){
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
 int i=30,j=0;
 while(fgets(readLine,256,fpt)!=NULL){
  if(strstr(readLine,check1)!=NULL){
   if(strstr(readLine,check2)!=NULL){
    i=30;
    for(j=0;j<=7;j++){
      cx[j] = readLine[i];
      i++;
    }i++;
    for(j=0;j<=7;j++){
      cy[j] = readLine[i];
      i++;
    }i++;
    for(j=0;j<=7;j++){
      cz[j] = readLine[i];
      i++;
    }
    pdb->CA[a].x = atof(cx);
    pdb->CA[a].y = atof(cy);
    a++;
   }
  }
 }
}
