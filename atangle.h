//SREL: Atomistic Angle Class to store and manipulate angle configurations from atomistic files  (Revision Date: 13th Sep 2023)
#ifndef _ATANGLE_H
#define _ATANGLE_H
#include "header.h"
class ATANGLE
{
	public:
		int partner1, partner2, partner3;
	 	ATANGLE(int _partner1, int _partner2, int _partner3){partner1=_partner1;        partner2=_partner2;	partner3=_partner3;}
		ATANGLE(){partner1=-1;      partner2=-1;	partner3=-1;}
};
#endif

