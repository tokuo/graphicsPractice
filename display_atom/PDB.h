#ifndef PDB_H
#define PDB_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Atom Atom;
struct Atom {
float x;
float y;
float z;
char resName[4];
int resNumber;
float tempFactor;
float occupancy;
char atomName[5];
char element[3];
};

typedef struct Bond Bond;
struct Bond {
Atom start;
Atom end;
};

typedef struct recordPDB recordPDB;
struct recordPDB {
Atom atom;
recordPDB* nextAtom;
recordPDB* nextCA;
};

typedef struct PDB PDB;
struct PDB {
int numAtom;
int numCA;
Atom Center;
float maxRadius;
Atom min;
Atom max;
recordPDB* top;
recordPDB* topCA;
recordPDB* current;
recordPDB* currentCA;
};

#endif
