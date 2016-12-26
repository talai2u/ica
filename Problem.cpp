#include"myAlgorithm.h"
using namespace std;


Problem::Problem(int dimension,double LowerLimit, double UpperLimit,int ProblemType):_dimension(dimension),_LowerLimit(LowerLimit),_UpperLimit(UpperLimit),ProblemType(ProblemType)
{}

ostream& operator<< (ostream& os, const Problem& pbm){
	os<<"    Dimension du probleme: "<<pbm.dimension() << endl;
	os<<"    Valeur Min: "<<pbm.LowerLimit()<< endl <<"    Valeur Max: "<<pbm.UpperLimit()<<endl;
	return os;
}
istream& operator>> (istream& is, Problem& pbm){
	cout<<"Entrer la dimension du probleme: ";
	is>>pbm._dimension;
		is>>pbm._LowerLimit;
	cout<<"Entrer la valeur maximale: ";
	is>>pbm._UpperLimit;
}

Problem& Problem::operator=  (const Problem& pbm){
	if (*this != pbm)
	{
	_dimension= pbm.dimension();
	_LowerLimit=pbm.LowerLimit();
	_UpperLimit=pbm.UpperLimit();
	}
	return *this;	

}
bool Problem::operator== (const Problem& pbm) const{
	if (dimension() != pbm.dimension()) return false;
	if (LowerLimit() != pbm.LowerLimit()) return false;
	if (UpperLimit() != pbm.UpperLimit()) return false;
	return true;
}

bool Problem::operator!= (const Problem& pbm) const{
	if (dimension() != pbm.dimension()) return true;
	if (LowerLimit() != pbm.LowerLimit()) return true;
	if (UpperLimit() != pbm.UpperLimit()) return true;
	return false;
}

int Problem::dimension() const
{	
	 return _dimension;
}
double Problem::LowerLimit() const
{  
   return _LowerLimit;
}
double Problem::UpperLimit() const
{
   return _UpperLimit;
}


