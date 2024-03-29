//Contains all the data writing files (XTC, PDB, GRO, DUMP, SREL progress, ITP, PSF, Parameter for DMD
//Edited on 13th Sept 2023
#ifndef _WRITEFILES_H
#define _WRITEFILES_H
//Headers needed in writefiles.cpp
#include "system.h"

class WriteFiles
{
	public:
		System S;				//To get all the variables for naming files

//For PDB initial system, to go along with dcd
	void PDBFile(vector<Particle>&, std::string);
//For movies (LAMMPS Traj format)
	void WriteDump(double, vector<Particle>&, int, double, std::string);
};
#endif
	
