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
typedef struct Bond Bond;
struct Bond {
Atom start;
Atom end;
};
extern void bondDraw(FILE* fpt, float startx, float starty, float endx, float
endy);
extern void bondDraw2(FILE* fpt, Bond l);

#endif