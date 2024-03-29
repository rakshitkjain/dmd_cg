//SREL: CG Bond Class to store and manipulate bonded atoms for DMD along with the type of bond stored  (Revision Date: 13th Sep 2023)
#ifndef _CGBOND_H
#define _CGBOND_H
#include "header.h"
class CGBOND
{
	public:
		int partner1, partner2, middle;
//		std::string type;	
		double bondlength;					
	 	BOND(int _partner1, int _partner2, int _middle, double _bondlength){partner1=_partner1;        partner2=_partner2;   middle=_middle; bondlength=_bondlength;}
		BOND(){partner1=-1;      partner2=-1;  middle=-1;	bondlength=0.0;}
};
#endif

//middle = -1 means normal bond. middle > 0  means angle bond 
//partner1 is the smaller atom number and partner2 is the bigger one
//ADD METHOD TO STORE DIHEDRAL BOND TOO
