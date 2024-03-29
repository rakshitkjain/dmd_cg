//SREL: atbead.h Atomistic Bead Class (Revision Date: 13th Sep 2023)
//Store the list of atomistic bead particles from traj and input config files
#ifndef _ATBEAD_H
#define _ATBEAD_H
#include "header.h"
#include "xyz.h"
class ATBEAD
{
public:
	XYZ coordinate;					//coordinates
	std::string type;				//Type of atom: ATOM/HETATOM etc.
	std::string name;				//Atom name which incorporates the geometry (N2, C3 etc)
	std::string resname;				//Residue name for the particle (CT2, ACY etc)
	char chaintype;				//Chaintype, to identify multiples of same residue (C, A, W etc)
	int chainnumber;				//Each chain has a different number and different residues have a different number
	double occupancy;				//Still NOT CLEAR ON THESE TWO
	double tempfactor;				//Still NOT CLEAR ON THESE TWO
	std::string moltype;				//Name of molecule, helps to join residues which are joined
	std::string atomtype;				//Special name for the atom, useful when reading parameters fron .par file. Initialized when reading a psf
	std::string symbol;				//Symbol of the element concerning the molecule
	double mass;					//Mass of the particle
	double diameter;				//Diameter of the particle
	double charge;					//Charge on the particle (might be useful for Ewald Summation later)
	//Sample initializer
	Particle(){coordinate.x=0.0; coordinate.y=0.0; coordinate.z=0.0; type="ATOM"; name="C1"; resname="CHI"; chaintype='A'; chainnumber=1; occupancy=0.0; tempfactor=0.0; moltype="CHI"; atomtype = "CG331"; symbol="C"; diameter = 1.0; mass = 1.0; charge = 500.0;}
};
#endif
//Particle(){coordinate.x=0.0; coordinate.y=0.0; coordinate.z=0.0; type="ATOM"; name="C1"; resname="CHI"; chaintype='A'; chainnumber=1; occupancy=0.0; tempfactor=0.0; moltype="CHI"; atomtype = "CG331"; symbol="C"; diameter = 1.0; mass = 1.0; charge = 0.0;}
