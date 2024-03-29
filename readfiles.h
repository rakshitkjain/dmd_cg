//Contains all the functions for reading data files (PDB, PSF, GRO, ITP, XTC)
//Modified  on 13th Sept 2023
#ifndef _READFILES_H
#define _READFILES_H
//Headers needed in readfiles.cpp
#include "atbead.h"
#include "atbond.h"
#include "atangle.h"
#include "atdihedral.h"

class ReadFiles
{
	public:
		vector<std::string> atomtype_vector;//Find if this is actually being used
	//Reading Atomistic Config PDB File
	void ReadPDBFile(std::string, vector<Particle>&, vector<double>&);
	//Reading Atomistic Config PSF File
	void ReadPSFFile(std::string, vector<Particle>&, vector<BOND>&, vector<NONBOND>&);
	//Reading Atomistic Config GRO File
	void ReadGROFile(std::string, vector<Particle>&, vector<double>&);
	//Reading Atomistic Config ITP File
        void ReadITPFile(std::string, vector<Particle>&, vector<ATBOND>&, vector<ATANGLE>&, vector<ATDIHEDRAL>&);
};
#endif

