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
};

typedef struct arrayPDB arrayPDB;
struct arrayPDB {
int numAtom;
int numCAAtom;
Atom *CA;
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
recordPDB* top;
recordPDB* topCA;
recordPDB* current;
recordPDB* currentCA;
}; 

extern void bondDraw(FILE* fpt, float startx, float starty, float endx, float
endy);
extern void bondDraw2(FILE* fpt, Bond l);

#endif
