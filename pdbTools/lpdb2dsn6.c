#include <math.h>
#include "./pdb.h"
#include "./DSN6.h"
#include "./pdb2dsn6.h"

void
lpdb2dsn6(pdbFile* pdb, Dsn6* dens, lpdb2dsn6Info linfo, int mode)
{
	pdbCoord mean;
	double	 max;
	int ix, iy, iz;
	int n;
	int Z;
	double x, y, z;
	double r;
	double Max, Min;	
	double R;
	double aH = 0.0529e-9;
	double  K = 9.0e9;
	double  e = 1.6e-19;

	pdbAreaInfo(pdb, &mean, &max, 0);
	fprintf(stdout, "mean %15.6f %15.6f %15.6f\n", mean.x, mean.y, mean.z);
	fprintf(stdout, "max %15.6f\n", max);
	dsn6Init(dens, 0);

	dens->Dsn6Header.Start.x = (mean.x - max - 10)/linfo.SamplingRate - 1;
	dens->Dsn6Header.Start.y = (mean.y - max - 10)/linfo.SamplingRate - 1;
	dens->Dsn6Header.Start.z = (mean.z - max - 10)/linfo.SamplingRate - 1;

	dens->Dsn6Header.Extent.x = (2*max + 20)/linfo.SamplingRate + 1;
	dens->Dsn6Header.Extent.y = (2*max + 20)/linfo.SamplingRate + 1;
	dens->Dsn6Header.Extent.z = (2*max + 20)/linfo.SamplingRate + 1;

	dens->Dsn6Header.SamplingRate.x = 1;
	dens->Dsn6Header.SamplingRate.y = 1;
	dens->Dsn6Header.SamplingRate.z = 1;

	fprintf(stdout, "Start  %5d %5d %5d\n", dens->Dsn6Header.Start.x, dens->Dsn6Header.Start.y, dens->Dsn6Header.Start.z);
	fprintf(stdout, "Extent %5d %5d %5d\n", dens->Dsn6Header.Extent.x, dens->Dsn6Header.Extent.y, dens->Dsn6Header.Extent.z);
	dsn6ImageAllocate(dens, 0);

	/* Density Calculation */
	fprintf(stdout, "Density Calculation Start ---- \n");
	pdb->current = pdb->top;
	while(NULL!=pdb->current) {
		if(pdbIsAtom(pdb->current)) {
			if(pdb->current->atomSerialNumber%100==0) {
				fprintf(stdout, "%d / %d\n", pdb->current->atomSerialNumber, pdb->nAtom);
			}
			for(x=pdb->current->coord.x-10; x<pdb->current->coord.x+10; x+=linfo.SamplingRate/5) {
				ix = (x/linfo.SamplingRate +0.5) - dens->Dsn6Header.Start.x;
			for(y=pdb->current->coord.y-10; y<pdb->current->coord.y+10; y+=linfo.SamplingRate/5) {
				iy = (y/linfo.SamplingRate +0.5) - dens->Dsn6Header.Start.y;
			for(z=pdb->current->coord.z-10; z<pdb->current->coord.z+10; z+=linfo.SamplingRate/5) {
				iz = (z/linfo.SamplingRate +0.5) - dens->Dsn6Header.Start.z;

				r = sqrt((pdb->current->coord.x - x)*(pdb->current->coord.x - x)
					+(pdb->current->coord.y - y)*(pdb->current->coord.y - y)
					+(pdb->current->coord.z - z)*(pdb->current->coord.z - z));
				if(r<linfo.SamplingRate/5 || 10<r ) {
					;	
				} else {	
					n = ix  
					  + iy*dens->Dsn6Header.Extent.x + 
					  + iz*dens->Dsn6Header.Extent.x*dens->Dsn6Header.Extent.y;
					r *= 1e-10;
					Z = pdbZValueGet(pdb->current);
					R = aH*pow(Z, -1/3);
					/* Wentzel Atom Model */
					dens->FloatImage[n] += (K*e*Z/r)*exp(-r/R); 
				}
			}
			}
			}
		}
		pdb->current = pdb->current->next;
	}

	Min = Max = dens->FloatImage[0];;	
	for(ix=0; ix<dens->Dsn6Header.Extent.x; ix++) {
	for(iy=0; iy<dens->Dsn6Header.Extent.y; iy++) {
	for(iz=0; iz<dens->Dsn6Header.Extent.z; iz++) {
		n =  ix + iy*dens->Dsn6Header.Extent.x + iz*dens->Dsn6Header.Extent.x*dens->Dsn6Header.Extent.y;
		if(Max<dens->FloatImage[n]) {
			Max = dens->FloatImage[n];
		}	
		if(dens->FloatImage[n]<Min) {
			Min = dens->FloatImage[n];
		}	
	}
	}
	}

	fprintf(stdout, "min-max %15.6f %15.6f\n", Min, Max);
	dens->Dsn6Header.DensScaling = (254.0)/(Max - Min)*dens->Dsn6Header.Weight;
	dens->Dsn6Header.DensOffset  = (int)(0.5 - dens->Dsn6Header.DensScaling*Min);

	dens->Dsn6Header.ACellEdge = linfo.SamplingRate*dens->Dsn6Header.CellConstantScalingFactor;
	dens->Dsn6Header.BCellEdge = linfo.SamplingRate*dens->Dsn6Header.CellConstantScalingFactor;
	dens->Dsn6Header.CCellEdge = linfo.SamplingRate*dens->Dsn6Header.CellConstantScalingFactor;
}
