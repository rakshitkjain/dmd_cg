//SREL: Atomistic Bond Class to store and manipulate bonded atoms from atomistic files  (Revision Date: 13th Sep 2023)
#ifndef _ATBOND_H
#define _ATBOND_H
#include "header.h"
class ATBOND
{
	public:
		int partner1, partner2;
	 	ATBOND(int _partner1, int _partner2){partner1=_partner1;        partner2=_partner2;}
		ATBOND(){partner1=-1;      partner2=-1;}
};
#endif

