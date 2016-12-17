#include"PDB.h"

// input List
void pdbRead(FILE* fpt, PDB *pdb){
 char readLine[80];
 char check1[] = "ATOM";
 char check2[] = "CA";
 char cx[8],cy[8],cz[8];
 char resNumber[4],tempFactor[6],occupancy[5];
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
   i=30;
   for(j=0;j<=7;j++){
     cx[j] = readLine[i];
     i++;
   }
   pdb->current->atom.x = atof(cx);
   for(j=0;j<=7;j++){
     cy[j] = readLine[i];
     i++;
   }
   pdb->current->atom.y = atof(cy);
   for(j=0;j<=7;j++){
     cz[j] = readLine[i];
     i++;
   }
   pdb->current->atom.z = atof(cz);
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
    for(j=0;j<=7;j++){
      cz[j] = readLine[i];
      i++;
    }
    pdb->currentCA->atom.x = atof(cx);
    pdb->currentCA->atom.y = atof(cy);
    pdb->currentCA->atom->atom.z = atof(cz);
   }
   // extension part
   i=17;
   for(j=0;j<3;j++){ 
    pdb->current->atom.resName[j] = readLine[i];
    i++;
   }
   i=22;
   for(j=0;j<4;j++){
    resNumber[j] = readLine[i];
    i++;
   }
   pdb->current->atom.resNumber = atoi(resNumber);
   i=61;
   for(j=0;j<6;j++){
    tempFactor[j] = readLine[i];
    i++;
   }
   pdb->current->atom.tempFactor = atof(tempFactor);
   i=55;
   for(j=0;j<5;j++){
    occupancy[j] = readLine[i];
    i++;
   }
   pdb->current->atom.occupancy = atof(occupancy);
   i=13;
   for(j=0;j<4;j++){
    pdb->current->atom.atomName[j] = readLine[i]; 
    i++;
   }
   i=77;
   for(j=0;j<2;j++){ 
    pdb->current->atom.element[j] = readLine[i];
    i++;
   }
  }
 }
 pdb->current->nextAtom = NULL;
 pdb->currentCA->nextCA = NULL;
}


// input array
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
    //pdb->CA[a].z = atof(cz);
    a++;
   }
  }
 }
}
