//SREL: Atomistic Dihedral Class to store and manipulate dihedral angle configurations from atomistic files  (Revision Date: 13th Sep 2023)
#ifndef _ATDIHEDRAL_H
#define _ATDIHEDRAL_H
#include "header.h"
class ATDIHEDRAL
{
	public:
		int partner1, partner2, partner3, partner4;
	 	ATDIHEDRAL(int _partner1, int _partner2, int _partner3, int _partner4){partner1=_partner1;        partner2=_partner2;	partner3=_partner3;	partner4=_partner4}
		ATDIHEDRAL(){partner1=-1;      partner2=-1;	partner3=-1;	partner4=-1;}
};
#endif

