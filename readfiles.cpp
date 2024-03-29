#include "readfiles.h"
//Reading PDB files 
void ReadFiles::ReadPDBFile(std::string FileName, vector<Particle> &P, vector<double> &parameters)
{
	Particle p;
	std::string dumps1, dumps2, dumps, line;
	double a, b, c, gamma, alpha, beta;

	int cryst_line = 0, remark_line = 0, test;
	int particle_number;
//TO check if the first two lines are of Remark or CRYST1
	ifstream in;
	in.open(FileName);
		std::getline(in,dumps1);
		std::getline(in,dumps2);
	in.close();
	std::string remark ="REMARK";
	std::string cryst="CRYST1";
	size_t remark_position= dumps1.find(remark);
//This means that there is no 'REMARK' in 1st line line
	if(remark_position == std::string::npos)			
	{
		remark_position= dumps2.find(remark);
		//This means that there is a 'REMARK' in 2nd line
		if(remark_position != std::string::npos)		
		{
			remark_line = 2;
			size_t cryst_position = dumps1.find(cryst);
			if(cryst_position != std::string::npos)		//1st line is the cryst line
				{cryst_line = 1;}
			else
				{cryst_line = 0;}			//No cryst line
		}
		else
		{
			remark_line = 0;					//No remark line
			size_t cryst_position = dumps1.find(cryst);
			if(cryst_position != std::string::npos)			//1st line is the cryst line
				{cryst_line = 1;}
			else
			{
				size_t cryst_position = dumps2.find(cryst);
				if(cryst_position != std::string::npos)		//2nd line is the cryst line
					{cryst_line = 2;}
				else
					{cryst_line = 0;}			//No cryst line
			}
		}
	}
	else							//Remark is in the 1st line
	{
		remark_line = 1;
		size_t cryst_position = dumps2.find(cryst);
		if(cryst_position != std::string::npos)		//2nd line is the cryst line
			{cryst_line = 2;}
		else
			{cryst_line = 0;}			//No cryst line
	}
	try 
	{
		if(cryst_line == 1)
		{
			in.open(FileName);
				in>>dumps>>a>>b>>c>>alpha>>beta>>gamma;
			in.close();
			throw 1;
		}
		else if(cryst_line == 2)
		{
			in.open(FileName);
				std::getline(in,dumps);
				in>>dumps>>a>>b>>c>>alpha>>beta>>gamma;
			in.close();
			throw 2;
		}
		else if(cryst_line == 0)
			{throw 0;}
	}
	catch(int x)
	{
		test = x;
		if(x!=0)
		{
			if(a <= parameters[0] && b <= parameters[1] && c <= parameters[2] && alpha == parameters[3] && beta == parameters[4] && gamma == parameters[5])
				{cout<<"Everything is fine, start reading the main file"<<endl;}
			else
				{cout<<"PDB file reading error, You gon done a mistake in the CRYST1 field"<<endl;}
		}
	}
//Now get the remark/cryst lines from the PDB
	in.open(FileName);
		if((test == 2 && remark_line == 0) || (test==1 && remark_line ==2))
		{
			std::getline(in,dumps);
			std::getline(in,dumps);
//			cout<<dumps<<endl;
		}
		else if((test ==1 && remark_line == 0) || (test==0 && remark_line ==1) )
		{
			std::getline(in,dumps);
//			cout<<dumps<<endl;
		}
		int count = 0;	
//		std::istringstream chaintypestream, chainnumberstream, coordinatestream, diameterstream, occupancystream;		
		while(!in.eof())
		{
			std::getline(in,line);
//			cout<<line<<endl;
			//Now start reading the lines for the data
			if(line.find("ATOM") != std::string::npos )
			{
				p.type = line.substr(0,4);
				std::istringstream particle_numberstream(line.substr(6,5));
				particle_numberstream >> particle_number;
				p.name = line.substr(12,4);
				p.resname = line.substr(17,3);
				std::istringstream chaintypestream(line.substr(21,1));
				chaintypestream >> p.chaintype;
				std::istringstream chainnumberstream(line.substr(22,4));
				chainnumberstream >> p.chainnumber;
				std::istringstream coordinatestream(line.substr(30,24));
				coordinatestream >> p.coordinate.x >> p.coordinate.y >> p.coordinate.z;
				std::istringstream occupancystream(line.substr(54,6));
				occupancystream >> p.occupancy;
//				p.tempfactor = line.substr(60,6);//Will write the diameter instead of temp factor while creating pdb file
				std::istringstream diameterstream(line.substr(60,6));
				diameterstream >> p.diameter;
				p.moltype = line.substr(72,4);
				p.symbol = line.substr(76,2);
//				cout<<"Read some stuff from the file "<<particle_number<<endl;
				if(count + 1 == particle_number)
				{
					P.push_back(p);
				}
				else	
				{
					cerr<<"You done goofed up in reading particle number and for particle number = "<<particle_number<<endl;
					exit(1);
				}
			}
			else if(line.find("HETATM") != std::string::npos)
			{
				p.type = line.substr(0,6);
				std::istringstream particle_numberstream(line.substr(8,5));
				particle_numberstream >> particle_number;
				p.name = line.substr(14,4);
				p.resname = line.substr(19,3);
				std::istringstream chaintypestream(line.substr(23,1));
				chaintypestream >> p.chaintype;
				std::istringstream chainnumberstream(line.substr(24,4));
				chainnumberstream >> p.chainnumber;
				std::istringstream coordinatestream(line.substr(32,24));
				coordinatestream >> p.coordinate.x >> p.coordinate.y >> p.coordinate.z;
				std::istringstream occupancystream(line.substr(56,6));
				occupancystream >> p.occupancy;
//				p.tempfactor = line.substr(62,6);
				std::istringstream diameterstream(line.substr(62,6));
				diameterstream >> p.diameter;
				p.moltype = line.substr(74,4);
				p.symbol = line.substr(78,2);
//				cout<<"Read some stuff from the file "<<particle_number<<endl;
				if(count + 1 == particle_number)
				{
					P.push_back(p);
				}
				else	
				{
					cerr<<"You done goofed up in reading particle number and for particle number = "<<particle_number<<endl;
					exit(1);
				}
			}
			count = count+1;
		}
	in.close();
	cout<<"Read the pdb file completely"<<endl;
}
//Reading PSF files for bonds, pseudobonds, NOTHING FOR DIHEDRAL RIGHT NOW, charge, mass and names for parameter file
void ReadFiles::ReadPSFFile(std::string FileName, vector<Particle> &P, vector<BOND> &bondlist, vector<NONBOND> &nonbondlist)
{
	std::string line;
	bool natom_found=false, nbond_found=false, anglebond_found = false, atomtype_found = false, diditfeed;
	bool swapped;
	int n_residue, n_bonds, n_angles, bond_counter = 0, bond_number, angle_counter = 0, angle_number;
	int bond[8], anglebonds[9];			//Taking in multiple bonds and pseudobonds from angles
	BOND feed_bond, feed_pseudo, bond_orderer;	//feeder for covalent bond and pseudobonds
	NONBOND filler;
//This is needed bcoz vector::insert needs an iterator variable
	auto iterator=bondlist.begin();
	double charge, mass;
	int particle_number = 0, chainnumber, dump;
	std::string name, moltype, resname, atomtype;

	ifstream in;
	in.open(FileName);
		std::getline(in,line);
//		cout<<line<<endl;
		while(!in.eof())
		{
			//Atom records not found condition
			while((line.find("!NATOM")) == std::string::npos)			
			{
				std::getline(in,line);
//				cout<<line<<endl;
			}
			natom_found = true;
			std::istringstream linestream(line);
			linestream >> n_residue;			//Number of atom records in the file
//			cout<<"n_residue = "<<n_residue<<endl;
//			while((line.find("!NATOM")) != std::string::npos)
			while(particle_number < n_residue)
			{
//				std::getline(in,line);
//				cout<<line<<endl;
				in >> particle_number >> moltype >> chainnumber >> resname >> name >> atomtype >> charge >> mass >> dump;
//cout<<particle_number<<"\t"<<moltype<<"\t"<<chainnumber<<" \t"<<resname<<"\t"<<name<<"\t"<<atomtype<<" \t"<<charge<<"\t"<<mass<<"\t"<<dump<<endl;
//				if(P[particle_number - 1].moltype != moltype)
//				{
//					cout<<"Error when reading moltype for particle number"<<particle_number<<endl;
//					cout<<"Moltype = "<<P[particle_number - 1].moltype<<"read moltype = "<<moltype<<endl;
//					exit(1);
//				}
				if(P[particle_number - 1].chainnumber != chainnumber)
				{
					cout<<"Error when reading chainnumber for particle number"<<particle_number<<endl;
					exit(1);
				}
				else if(P[particle_number - 1].resname != resname)
				{
					cout<<"Error when reading resname for particle number"<<particle_number<<endl;
					exit(1);
				}
//				else if(P[particle_number - 1].name != name)
//				{
//					cout<<"Error when reading name for particle number"<<particle_number<<endl;
//					exit(1);
//				}
//This means all the entries are fine in the psf file, matching with the pdb file, so take data from psf
				else		
				{
					P[particle_number-1].charge = charge;
					P[particle_number-1].mass = mass;
					P[particle_number-1].atomtype.replace(P[particle_number-1].atomtype.begin(), P[particle_number-1].atomtype.end(), atomtype);
//					cout<<"particle_number-1 = "<<particle_number-1<<"\t atomtype = "<<P[particle_number-1].atomtype<<endl;					
				}	
			}
//			else
//			{
//				cout<<"Something fishy with psf file while taking mass and charge, recheck it"<<endl;
//			}
			//Now start to collect bond records
			//Bond records not found condition
			while((line.find("!NBOND")) == std::string::npos)			
			{
				std::getline(in,line);
//				cout<<line<<endl;
			}
			nbond_found = true;
			std::istringstream linestream1(line);
			linestream1 >> n_bonds;
			bond_number = n_bonds - (n_bonds%4);
			//Now, each line till bond_number is reached, will have 4 bonds 
			while(bond_counter < bond_number)			
			{
				in>>bond[0]>>bond[1]>>bond[2]>>bond[3]>>bond[4]>>bond[5]>>bond[6]>>bond[7];
//				cout<<bond[0]<<"\t"<<bond[1]<<"\t"<<bond[2]<<"\t"<<bond[3]<<"\t"<<bond[4]<<" \t"<<bond[5]<<"\t"<<bond[6]<<"\t"<<bond[7]<<endl;
				for(int i = 0; i<8; i=i+2)
				{
					if(bond[i]<bond[i+1])
					{
						//Sorting them into smaller particle first
						feed_bond.partner1 = bond[i]-1;		
						feed_bond.partner2 = bond[i+1]-1;
						feed_bond.middle = -1;
					}
					else if(bond[i] > bond[i+1])
					{
						feed_bond.partner1 = bond[i + 1]-1;
						feed_bond.partner2 = bond[i]-1;
						feed_bond.middle = -1;
					}
					bondlist.push_back(feed_bond);
				}
				bond_counter = bond_counter + 4;
			}
			//Now, take whatever amount of bonds remain in the file
			//Will not enter here if n_bonds%4==0
			while(bond_counter < n_bonds)			
			{
				//Means only one bond left
				if(n_bonds%4 ==1)
					{in>>bond[0]>>bond[1];}
				//Means only two bonds left
				else if(n_bonds%4 ==2)
					{in>>bond[0]>>bond[1]>>bond[2]>>bond[3];}
				//Means only three bonds left
				else if(n_bonds%4 ==3)
					{in>>bond[0]>>bond[1]>>bond[2]>>bond[3]>>bond[4]>>bond[5];}
				else
				{	
					cout<<"Some erroring in reading the bonds from psf file, counter should NOT be here!!"<<endl;
					exit(1);
				}
				for(int i = 0; i<2*(n_bonds%4); i = i+2)
				{
					if(bond[i]<bond[i+1])
					{
						feed_bond.partner1 = bond[i]-1;
						feed_bond.partner2 = bond[i+1]-1;
						feed_bond.middle = -1;
					}
					else if(bond[i] > bond[i+1])
					{
						feed_bond.partner1 = bond[i + 1]-1;
						feed_bond.partner2 = bond[i]-1;
						feed_bond.middle = -1;
					}
					bondlist.push_back(feed_bond);
					bond_counter = bond_counter + 1;
				}
			}
//			else
//			{
//				cout<<"Something fishy with psf file when taking in bonds, recheck it"<<endl;
//			}
			//Now read the angles as pseudobonds and use the values for parameters iff you want to keep it fixed
			//Angle records not found condition
			while((line.find("!NTHETA")) == std::string::npos)			
			{
				std::getline(in,line);
//				cout<<line<<endl;
			}

			anglebond_found = true;
			std::istringstream linestream2(line);
			linestream2 >> n_angles;
			angle_number = n_angles - (n_angles%3);
			while(angle_counter < angle_number)
			{
				in>>anglebonds[0]>>anglebonds[1]>>anglebonds[2]>>anglebonds[3]>>anglebonds[4]>>anglebonds[5]>>anglebonds[6]>>anglebonds[7]>>anglebonds[8];
//cout<<anglebonds[0]<<"\t"<<anglebonds[1]<<"\t"<<anglebonds[2]<<"\t"<<anglebonds[3]<<"\t"<<anglebonds[4]<<" \t"<<anglebonds[5]<<"\t"<<anglebonds[6]<<"\t"<<anglebonds[7]<<"\t"<<anglebonds[8]<<endl;
				for(int i = 0; i<9; i=i+3)
				{
//Placing the anglebond near previous bond occurence for that first atom, makes it easy to order the bondlist
					diditfeed = false;
					if(anglebonds[i]<anglebonds[i+2])
					{
						feed_pseudo.partner1 = anglebonds[i]-1;
						feed_pseudo.partner2 = anglebonds[i+2]-1;
						feed_pseudo.middle = anglebonds[i+1]-1;
						for(int q=0; q<bondlist.size(); q++)
						{
							if(bondlist[q].partner1==anglebonds[i]-1)
							{
								iterator=bondlist.begin();
								bondlist.insert(iterator+q, feed_pseudo);
								diditfeed=true;
								break;
							}
						}
					}
					else if(anglebonds[i] > anglebonds[i+2])
					{
						feed_pseudo.partner1 = anglebonds[i + 2]-1;
						feed_pseudo.partner2 = anglebonds[i]-1;
						feed_pseudo.middle = anglebonds[i+1]-1;
						for(int q=0; q<bondlist.size(); q++)
						{
							if(bondlist[q].partner1==anglebonds[i+2]-1)
							{
								iterator=bondlist.begin();
								bondlist.insert(iterator+q, feed_pseudo);
								diditfeed=true;
								break;
							}
						}
					}
					if(!diditfeed)
						{bondlist.push_back(feed_pseudo);}
				}
				angle_counter = angle_counter +3;
			}
			while(angle_counter < n_angles)
			{
				if(n_angles%3 == 1)
					{in>>anglebonds[0]>>anglebonds[1]>>anglebonds[2];}
				else if (n_angles%3 == 2)
					{in>>anglebonds[0]>>anglebonds[1]>>anglebonds[2]>>anglebonds[3]>> anglebonds[4]>>anglebonds[5];}
				else
				{	
					cout<<"Some erroring in reading the angles from psf file, counter should NOT be here!!"<<endl;
					exit(1);
				}
				for(int i = 0; i<3*(n_angles%3); i=i+3)
				{
//Placing the anglebond near previous bond occurence for that first atom, makes it easy to order the bondlist
					diditfeed = false;
					if(anglebonds[i]<anglebonds[i+2])
					{
						feed_pseudo.partner1 = anglebonds[i]-1;
						feed_pseudo.partner2 = anglebonds[i+2]-1;
						feed_pseudo.middle = anglebonds[i+1]-1;
						for(int q=0; q<bondlist.size(); q++)
						{
							if(bondlist[q].partner1==anglebonds[i]-1)
							{
								iterator=bondlist.begin();
								bondlist.insert(iterator+q, feed_pseudo);
								diditfeed=true;
								break;
							}
						}
					}
					else if(anglebonds[i] > anglebonds[i+2])
					{
						feed_pseudo.partner1 = anglebonds[i + 2]-1;
						feed_pseudo.partner2 = anglebonds[i]-1;
						feed_pseudo.middle = anglebonds[i+1]-1;
						for(int q=0; q<bondlist.size(); q++)
						{
							if(bondlist[q].partner1==anglebonds[i+2]-1)
							{
								iterator=bondlist.begin();
								bondlist.insert(iterator+q, feed_pseudo);
								diditfeed=true;
								break;
							}
						}
					}
					if(!diditfeed)
						{bondlist.push_back(feed_pseudo);}
					angle_counter = angle_counter +1;
				}
			}
			break;
		}
//		cout<<"Closed PSF file"<<endl;
		if(!natom_found || !nbond_found || !anglebond_found)
		{
			cout<<"You did a booboo in natom records in psf"<<endl;
			exit(1);
		}
	in.close();
	cout<<"Reading from psf file complete"<<endl;
}
//Reading GRO files, make sure to convert nm to angstroms, that is the unit used in DMD
void ReadFiles::ReadGROFile(std::string FileName, vector<Particle> &P, vector<double> &parameters)
{
	Particle p;
	std::string dumps1, dumps2, dumps, line;
	double totalP, a, b, c;
	int particle_number;
//Checking for the first line of remark and the number of atoms
	ifstream in;
	in.open(FileName);
		std::getline(in,dumps1);
		in>>totalP
	in.close();
//For GRO file, the first line is useless, so just ignore it
//totalP will be used as a check after reading the whole gro file
	cout<<"Total number of particles from GRO file: "<<totalP<<endl;
//Now start reading the main file
	in.open(FileName);
		std::getline(in,dumps);
		std::getline(in,dumps);
		int count = 0;
		while(!in.eof())
		{
			while(count < totalP)
			{
				std::getline(in,line);
				std::istringstream chainnumberstream(line.substr(0,5));
				chainnumberstream>>p.chainnumber;
				std::istringstream resnamestream(line.substr(5,5));
				resnamestream>>p.resname;
				std::istringstream namestream(line.substr(10,5));
				namestream>>p.name;
				std::istringstream atomnumberstream(line.substr(15,5));
				atomnumberstream>>particle_number;
				std::istringstream xccordstream(line.substr(20,8));
				std::istringstream ycoordstream(line.substr(28,8));
				std::istringstream zcoordstream(line.substr(36,8));
				xcoordstream>>p.coordinate.x;
				ycoordstream>>p.coordinate.y;
				zcoordstream>>p.coordinate.z;
				p.coordinate = p.coordinate*10.0;
				if(count+1 == particle_number)
				{
					P.push_back(p);
				}
				else
				{
					cerr<<"Made error while reading GRO file for particle number="<<particle_number<<endl;
				}
				count=count+1;
			}
			std::getline(in,line);
			std::istringstream astream(line.substr(0,10));
			std::istringstream bstream(line.substr(10,10));
			std::istringstream cstream(line.substr(20,10));
			astream>>parameters[0];
			bstream>>parameters[1];
			cstream>>parameters[2];
		}
	in.close();
	cout<<"Reading GRO File complete"<<endl;
}
//Reading ITP files for bonds, angles, dihedrals, charge, mass and atomtype names for parameter file
void ReadFiles::ReadITPFile(std::string FileName, vector<Particle> &P, vector<ATBOND> &bondlist, vector<ATANGLE> &anglelist, vector<ATDIHEDRAL> &dihedlist)
{
	std::string line;
	int particle_number, cgnr, chainnumber;
	int particle1, particle2, particle3, particle4;
	double charge, mass;
	ATBOND bond_feeder;
	ATANGLE angle_feeder;
	ATDIHEDRAL dihed_feeder;
	auto iterator=bondlist.begin();
	std::string atomtype, resname, name, dump;
	bool natom_found=false, nbond_found=false, nangle_found=false, ndihed_found=false, atomtype_found=false, diditfeed=false;

	ifstream in;
	in.open(FileName);
		while(!in.eof())
		{
			//Trying to find the line where atom records begin
			while(((line.find("[ atoms ]")) == std::string::npos) || ((line.find("resi")) == std::string::npos))
			{
				std::getline(in,line);
				cout<<line<<endl;
			}
			natom_found=true;
			std::getline(in,line);
			//Reading till we don't reach an empty line
			while(!line.empty())
			{
//				std::getline(in,line);
				cout<<line<<endl;
				std::istringstream linestream(line);
				linestream>>particle_number>>atomtype>>chainnumber>>resname>>name>>cgnr>>charge>>mass>>dump;
				if(particle_number != cgnr)
				{
					cout<<"Error in ITP, particle number not equal to cgnr, check file"<<endl;
				}
				diditfeed=false;
				//Feeding info into P vector
				for(int i = 0; i<P.size(); i++)
				{
					if(P[i].name == name && P[i].resname == resname)
					{
						P[i].atomtype=atomtype;
						P[i].charge=charge;
						P[i].mass=mass;
						diditfeed=true;
					}
				}
				std::getline(in,line);
			}
			//At this stage, hopefully all feeding is done. Check is to look at the charge of all atoms
			for(int i = 0; i<P.size(); i++)
			{
				if(P[i].charge == 500.0)
				{
					cout<<"Error  in feeding the charges/masses, not all fed"<<endl;
					exit(1);
				}
			}
			//Find the line where bonds begin
			while(((line.find("[ bonds ]")) == std::string::npos) || ((line.find("func")) == std::string::npos))
			{
				std::getline(in,line);
				cout<<line<<endl;
			}
			nbond_found=true;
			std::getline(in,line);
			//Reading till we don't reach an empty line
			while(!line.empty())
			{
				cout<<line<<endl;
				std::istringstream linestream(line);
				linestream>>particle1>>particle2>>dump;
				bond_feeder.partner1=particle1;
				bond_feeder.partner2=particle2;
				bondlist.push_back(bond_feeder);
				std::getline(in,line);
			}
			//Find the line where angles begin
			while(((line.find("[ angles ]")) == std::string::npos) || ((line.find("func")) == std::string::npos))
			{
				std::getline(in,line);
				cout<<line<<endl;
			}
			nangle_found=true;
			std::getline(in,line);
			//Reading till we don't reach an empty line
                        while(!line.empty())
			{
				cout<<line<<endl;
				std::istringstream linestream(line);
				linestream>>particle1>>particle2>>particle3>>dump;
				angle_feeder.partner1=particle1;
				angle_feeder.partner2=particle2;
				angle_feeder.partner3=particle3;
				anglelist.push_back(angle_feeder);
				std::getline(in,line);
			}
			//Find the line where dihedrals begin
			while(((line.find("[ dihedrals ]")) == std::string::npos) || ((line.find("func")) == std::string::npos))
			{
				std::getline(in,line);
				cout<<line<<endl;
			}
			ndihed_found=true;
			std::getline(in,line);
			//Reading till we don't reach an empty line
			while(!line.empty())
			{
				cout<<line<<endl;
				std::istringstream linestream(line);
				linestream>>particle1>>particle2>>particle3>>particle4>>dump;
				dihed_feeder.partner1=particle1;
				dihed_feeder.partner2=particle2;
				dihed_feeder.partner3=particle3;
				dihed_feeder.partner4=particle4;
				dihedlist.push_back(angle_feeder);
				std::getline(in,line);
			}
			break;
		}
		if(!natom_found || !nbond_found || !anglebond_found)
		{
			cout<<"You did a booboo in natom records in psf"<<endl;
			exit(1);
		}
	in.close();
	cout<<"Reading from ITP file complete"<<endl;
}








	
	
	
	
	
