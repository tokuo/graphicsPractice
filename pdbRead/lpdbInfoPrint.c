#include"PDB.h"

void lpdbInfoPrint(FILE* fpt, PDB* pdb){
 fprintf(fpt,"center: %f %f %f\nmaxRadius: %f\nmin: %f %f %f\nmax: %f %f %f\n",pdb->Center.x,pdb->Center.y,pdb->Center.z,pdb->maxRadius,pdb->min.x,pdb->min.y,pdb->min.z,pdb->max.x,pdb->max.y,pdb->max.z);
}
