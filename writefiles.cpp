#include "writefiles.h"

//PDB file to go along with DCD file, writing just once is fine.
void WriteFiles::PDBFile(vector<Particle> &P, std::string FileName)
{
	std::ostringstream fnd;//FileName dummy
        fnd<<FileName<<".pdb";
        std::string FileName1 = fnd.str();
        ofstream outputFile;
//Not appending right now, rewriting everytime
        outputFile.open(FileName1, std::ios::out);				

//REMARK original generated coordinate pdb file
//ATOM      1  N   CT2 A   1      34.512  35.455   4.217  1.00  0.00      CHI  N
//END
	outputFile<<"REMARK Writing PDB file for giung along with DCD"<<endl;
	for(int i = 0; i<S.N; i++)
	{
		outputFile<<setw(4)<<P[i].type<<"  "<<setw(5)<<i+1<<" "<<setw(4)<<P[i].name<<" "<<setw(3)<<P[i].resname<<" "<<P[i].chaintype<<setw(4)<<P[i].chainnumber<<"    "<<setw(8)<<setprecision(3)<<P[i].coordinate.x<<setw(8)<<setprecision(3)<<P[i].coordinate.y<<setw(8)<<setprecision(3)<<P[i].coordinate.z<<setw(6)<<setprecision(2)<<P[i].occupancy<<setw(6)<<setprecision(2)<<P[i].tempfactor<<"      "<<setw(4)<<P[i].moltype<<setw(2)<<P[i].symbol<<endl;
	}
	outputFile<<"END"<<endl;
	outputFile.close();
}
//For checking time variation of things, such as KE, etc 
void WriteFiles::TimeVarFileIni(std::string FileName)
{
	cout<<"Writing file for checking variation of parameters with time"<<endl;
	ofstream out;
	std::ostringstream fnd;							//FileName dummy
	fnd<<FileName<<".dat";
	std::string FileName1 = fnd.str();

	out.open(FileName1, ios::app);
		out<<"Time \t TE \t KE \t PE \t X momentum \t Y momentum \t Z momentum \t Temperature"<<endl;
	out.close();
}

//Writing file in the LAMMPS trajectory format for particle visualisation
void WriteFiles::WriteDump(double TIMESTEP, vector<Particle> &P, int N, double L, std::string FileName)
{
	std::ostringstream fnd;//FileName dummy
	fnd<<FileName<<".dump";
	std::string FileName1 = fnd.str();
//	sprintf(FileName,"_nc_%d_cl_%d_T_%lf_L_%d_m_%lf_s1_%lf_s2_%lf_bl_%lf_del_%lf_d_%lf.dump", nchain,chnlen,temp,L,mass,sigma1,sigma2,bondlen,del,delta);      
	
	ofstream out;
      out.open(FileName1,ios::app);
 
      out<<"ITEM: TIMESTEP"<<endl;
      out<<TIMESTEP<<endl;
      out<<"ITEM: NUMBER OF ATOMS"<<endl;
      out<<N<<endl;
      out<<"ITEM: BOX BOUNDS"<<endl;
      out<<0.0<<"\t"<<L<<endl;
      out<<0.0<<"\t"<<L<<endl;
      out<<0.0<<"\t"<<L<<endl;
      out<<"ITEM: ATOMS index type x y z"<<endl;
      string name;
      for(int i=0; i<N; i++)
      {
            name="1";
            out<<setw(6)<<i+1<<"\t"<<name<<"\t"<<setw(8)<<P[i].coordinate.x<<"\t"<<setw(8)<<P[i].coordinate.y<<"\t"<<setw(8)<<P[i].coordinate.z<<endl;
      }
      out.close();
}
