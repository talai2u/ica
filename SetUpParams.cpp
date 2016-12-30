#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "myAlgorithm.h"

using namespace std ;
SetUpParams::SetUpParams (){}
SetUpParams::~SetUpParams(){}//dest

SetUpParams::SetUpParams(int indep_runs,int nb_evol_steps,int pop_size,int sol_size, int max ,int numOfinitialImperialists , int numOfcountries /*, double impCost*/):
_independent_runs(indep_runs),//nombre de lancement
_nb_evolution_steps(nb_evol_steps),//nombre d'iteration
_population_size(pop_size), // colonies 
_solution_size(sol_size), // size of each particle
_maxCost(max),//le max de cost
_numOfinitialImperialists(numOfinitialImperialists),
_numOfcountries(numOfcountries)
//_imperalistCost(impCost);numOfinitialImperialists
{}

ostream& operator<< (ostream& os, const SetUpParams& setup)
{
	os <<endl<< " le nombre de lancement independant: "<< setup.independent_runs()<<endl;
	os << " le nombre d'iteration : "<< setup.nb_evolution_steps()<<endl;  
	os << " la taille de la colonie :: "<< setup.population_size()<<endl;
	os << " la taille de la solution est: " <<setup.solution_size()<<endl;
    os << " la taille de max "<<setup.maxCost()<<endl;
    os << " la taille De tab initial countries "<<setup.numOfinitialImperialists()<<endl;
    os << " le Nbr des payes "<<setup.numOfcountries()<<endl;
/*	os << " imperialist Cost "<<setup.imperialistCost()<<endl;*/
	return os; 	
}

istream& operator>> (istream& is, SetUpParams& setup){}

void SetUpParams::independent_runs(const unsigned int val)	{ _independent_runs = val; }
void SetUpParams::nb_evolution_steps(const unsigned int val)	{	 _nb_evolution_steps = val;}
void SetUpParams::population_size(const unsigned int val)	{	 _population_size = val;}
void SetUpParams::solution_size(const unsigned int val)		{	 _solution_size = val;}
void SetUpParams::maxCost(const unsigned val ){ _maxCost=val;   }
void SetUpParams::numOfinitialImperialists(const unsigned val ){ _numOfinitialImperialists=val;   }
void SetUpParams::numOfcountries(const unsigned val){ _numOfcountries=val;}
//void SetUpParams::imperliastCost(const double val ){ _imperalistCost=val;   }

const unsigned int SetUpParams::independent_runs() const 
{
	return _independent_runs; //nombre de lancement
}
const unsigned int SetUpParams::nb_evolution_steps() const 
{
	return _nb_evolution_steps;//nombre d'iteration
}
const unsigned int SetUpParams::population_size() const 
{	
	return _population_size;//size colonies
}
const unsigned int SetUpParams::solution_size() const 
{
	return _solution_size;//size of each article
}
const unsigned int SetUpParams::maxCost()const
{
	return _maxCost;
}
const unsigned int SetUpParams::numOfinitialImperialists()const
{
	return _numOfinitialImperialists;
}
const unsigned int SetUpParams::numOfcountries()const
{
	return _numOfcountries;
}




