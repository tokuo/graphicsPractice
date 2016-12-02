#include"PDB.h"


void pdbRead(FILE* fpt, PDB *pdb){
 char readLine[80];
 char check1[] = "ATOM";
 char check2[] = "CA";
 char cx[8],cy[8],cz[8];
 int i=30,j=0;
 pdb->numAtom = 0;
 pdb->numCA = 0;
 pdb->current = (recordPDB *)malloc(sizeof(recordPDB));
 pdb->top = (recordPDB *)malloc(sizeof(recordPDB));
 pdb->currentCA = (recordPDB *)malloc(sizeof(recordPDB));
 pdb->topCA = (recordPDB *)malloc(sizeof(recordPDB));
 pdb->current = pdb->top;
 pdb->currentCA = pdb->topCA;
 while(fgets(readLine,256,fpt)!=NULL){
  if(strstr(readLine,check1)!=NULL){
   if(pdb->numAtom != 0){
    pdb->current->nextAtom = (recordPDB *)malloc(sizeof(recordPDB));
    pdb->current = pdb->current->nextAtom;
   }
   pdb->numAtom++;
   if(strstr(readLine,check2)!=NULL){
    if(pdb->numCA != 0){
     pdb->currentCA->nextCA = (recordPDB *)malloc(sizeof(recordPDB));
     pdb->currentCA = pdb->currentCA->nextCA;
    }
    pdb->numCA++;
    i=30;
    for(j=0;j<=7;j++){
      cx[j] = readLine[i];
      i++;
    }
    for(j=0;j<=7;j++){
      cy[j] = readLine[i];
      i++;
    }
/*
    for(j=0;j<=7;j++){
      cz[j] = readLine[i];
      i++;
    }
*/
    pdb->currentCA->atom.x = atof(cx);
    pdb->currentCA->atom.y = atof(cy);
   }
  }
 }
 pdb->current->nextAtom = NULL;
 pdb->currentCA->nextCA = NULL;
}


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
    }
    for(j=0;j<=7;j++){
      cy[j] = readLine[i];
      i++;
    }
/*
    for(j=0;j<=7;j++){
      cz[j] = readLine[i];
      i++;
    }
*/
    pdb->CA[a].x = atof(cx);
    pdb->CA[a].y = atof(cy);
    a++;
   }
  }
 }
}
