#include"myAlgorithm.h"
#include <math.h> 

 using namespace std ;
 double PI=3.14159265358979323846;
 
 
 Solution::Solution( const Problem& pbm): _pbm(pbm),_solution(),_current_fitness()
 	{
 		initialize();
	}  
	
 Solution::Solution( const Solution& sol): _pbm(sol.pbm()),_solution(sol._solution),_current_fitness(sol.get_fitness()) 
 	{}

  ostream& operator<< (ostream& os, const Solution& sol)
	{
		os<<"	{";
		cout.precision(2);
	for(int i=0;i<sol._solution.size()-1;i++)
		{
      		os<<sol._solution[i] <<",";
		}

		os<<sol._solution[sol._solution.size()-1]<<"}";
		os<<" fitness: "<<sol._current_fitness;
	return os;
	}
	
   istream& operator>> (istream& is, Solution& sol)
	{
		cout<<"Entrer les donnees de Tab {  ";
	
	for(int i=0;i<sol._solution.size();i++)
		is>>sol._solution[i];
		cout<<"  } ";
	
	return is;
	}
	   Solution& Solution::operator=  (const Solution& sol)
	{
 	if(*this != sol)

 		{
			 _solution=sol._solution;
	 		this->_current_fitness=sol._current_fitness;
 		}
	 	 	 	return *this;

    }
    
   bool Solution::operator== (const Solution& sol) const
	{
		if (_solution != sol._solution)
		 { 
		 	return false;
		 }
		if (_current_fitness != sol._current_fitness) 
		{
			return false;
		}
	return true;
	}
	
  const Problem& Solution::pbm() const
	{
 		return _pbm;
	}
	
  void Solution::initialize()
	 {
		_solution.reserve(_pbm.dimension());	
	                                         //initialition de TAB du Solution 
		for(int i=0;i<_pbm.dimension();i++)
		{
			_solution.push_back(AlteaINT(_pbm.LowerLimit(),_pbm.UpperLimit()) ); //placé des variable Aléatoire  dans la tab
		}
 											//Mise à jour fitness
 	 _current_fitness=fitness();
	}
	
  double Solution::fitness()
    {
	//A faire
            switch(pbm().ProblemType()) {
                case 1: return Sphere(); break;
                case 2: return Rastrigin();break;
                case 3: return Ackley();break;
                case 4: return Rosenbrock();break;
                case 5: return Michalewicz();break;
	}
  
  double Solution::get_fitness() const 
		{
 			return _current_fitness; 
		}
  	
	/**
	 * Returns the fitness of one country
	 * @param individual the solution to evaluate
	 * @return the fitness
	 */
double Solution::getFitnessValue( vector<double> individual) 
	{
		double fitness = 0;		
		
		// Sphere function	
		for(int i=0; i<individual.size(); i++)
		{
			fitness = fitness + Math.pow(individual[i],2);
		}
		
//		// Rastrigin function	
//		for(int i=0; i<individual.size(); i++)
//		{
//			fitness = fitness + (Math.pow(individual[i],2)-10*Math.cos(2*Math.PI*individual[i]));
//		}
//		fitness = 10*dimension + fitness;
		
//		// Rosenbrock function
//		for(int i=0; i<individual.size()-1; i++)
//		{
//			fitness = fitness + 100*Math.pow((Math.pow(individual[i],2)-individual[i+1]),2) + Math.pow((individual[i]-1),2);
//		}
		
//		// Ackley function
//		double a = 20; 
//		double b = 0.2; 
//		double c = 2*Math.PI;
//		double s1 = 0; 
//		double s2 = 0;
//		for(int i=0; i<individual.size(); i++)
//		{
//			s1 = s1 + Math.pow(individual[i],2);
//			s2 = s2 + Math.cos(c*individual[i]);
//		}
//		fitness = -a * Math.exp( -b * Math.sqrt(1/individual.length*s1)) - Math.exp(1/individual.length*s2) + a + Math.exp(1);

		nbEvals++;
		return fitness;
	}
	
}
 unsigned int Solution::size() const
	{
 	return _solution.size();
	}
	
  vector<double>& Solution::solution()
  	{
	return _solution;
	}	
	
  double& Solution::position(const int index)
	{
		return _solution[index]; 
	}

  void Solution::position(const int index, const double value)
	{
		_solution[index]=value; //
	}


   /* class 
 ensemble des colonies peut etre des objet 
 colonie [contient un objet solution ]*/
 
   void Solution::setColoniesPosition( vector<vector<double>> coloniesPosition) 
	{
		this->coloniePosition=coloniePosition;
	}
	
   double Solution::getColoniesPosition() 
	{
		return coloniesPosition;
	}
   void Solution::setColoniesCost(vector<double> coloniesCost) 
	{
		this->coloniesCost = coloniesCost;
	}
   double Solution::getColoniesCost() 
	{
		return coloniesCost;
	}
  double Solution::getImperialistPosition() 
	{
		return imperialistPosition;
	}
  void Solution::setImperialistPosition( vector<double> imperialistPosition) 
	{
		this->imperialistPosition = imperialistPosition;
	}
  double Solution::getImperialistCost() 
	{
		return imperialistCost;
	}
  void Solution::setTotalCost(double totalCost) 
	{
		this->totalCost = totalCost;
	}
  void Solution::setImperialistCost(double imperialistCost) 
	{
		this->imperialistCost = imperialistCost;
	}
  void Solution::setColoniesPosition(vector<vector<double>> coloniesPosition) 
	{
		this->coloniesPosition = coloniesPosition;

	}
 
 //fonction de teste
	double Solution::Rastrigin()
	{
		double sol=0;  
	    
		for(int i=0;i<_solution.size();i++)
		sol+=(pow(_solution[i],2)-10*cos(2*PI*_solution[i]));
		
		
		return 10*_solution.size()+sol;
	}
	
	double Solution::Rosenbrock()
	{
	
	   double fitness= 0.0;
	
	    for (unsigned i = 0; i < _solution.size(); i++){
		fitness = fitness + 100*pow((pow(_solution[i],2)-_solution[i+1]),2)
	     }
	 
	
	     return fitness;
	 
	
	 }
	double Solution::Sphere()
	{
	double fitness= 0.0;
	
		for(int i=0;i<_solution.size();i++)
				fitness = fitness + pow(_solution[i],2);
			
		return  10*dimension + fitness;
	}
	
	
	double Solution::Ackley()
	{
		double a = 20; 
			double b = 0.2; 
			double c = 2*PI;
			double s1 = 0; 
			double s2 = 0;
		for(int i=0;i<_solution.size();i++)
		{
			s1+=pow(_solution[i],2);
			s2+=cos(c*_solution[i]);
	
		}
		    
		return -a*exp(-b*sqrt(1/_solution.size()*s1))-exp(1/_solution.size()*s2)+exp(1)+a;
	} 
	
	

