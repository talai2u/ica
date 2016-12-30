#ifndef ZFRACTION_H_INCLUDED
#define ZFRACTION_H_INCLUDED
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

//=======================================================================
  class Problem
  {
	public: 
		Problem();
		~Problem();

		friend ostream& operator<<(ostream& os, const Problem& pbm);
		friend istream& operator>>(istream& is, Problem& pbm);
		Problem& operator=(const Problem& pbm);
		bool operator==(const Problem& pbm) const;
		bool operator!=(const Problem& pbm) const;

		int dimension() const;		
		vector<double> LowerLimit() const;
        vector<double> UpperLimit() const;

	private:

		int _dimension;
		int _LowerLimit;
		int _UpperLimit;
        //vector<double> imperialistPosition;
  };
//=======================================================================
class Solution
  {
	//contient la déclaration d'une solution
	public:
		Solution (const Problem& pbm);
		Solution (const Solution& sol);
		~Solution();

 		friend ostream& operator<< (ostream& ost, const Solution& sol);
		friend istream& operator>> (istream& ist, Solution& sol);
		Solution& operator=  (const Solution& sol);
		bool operator== (const Solution& sol) const;
		bool operator!= (const Solution& sol) const;

		const Problem& pbm() const;	
		void initialize();
		double fitness();
		double get_fitness();
		double getFitnessValue( vector<double> individual);

  		
		unsigned int size() const;
     	vector<double>& solution();	
		double& position(const int index); //retournera une position du tableau _solution
        void  position(const int index, const double value);
	    
	    void setColoniesPosition( vector< vector<double> > coloniesPosition);
	    double getColoniesPosition();
	    void setColoniesCost(vector<double> coloniesCost);
	    double getColoniesCost();
	    double getImperialistPosition();
	    void setImperialistPosition( vector<double> imperialistPosition);
	    double getImperialistCost();
	    void setTotalCost(double totalCost);
	    void setImperialistCost(double imperialistCost);
	    void setColoniesPosition(double **coloniesPosition);

	private:
        vector<double> _solution;
        double _current_fitness;                  
		const Problem& _pbm;
		double **coloniesPosition;
     	vector<double> coloniesCost;
	    int problemDimension;
	    vector<double> imperialistPosition;
	    double imperialistCost;
	    double totalCost;
  };
  
  //=======================================================================

   class SetUpParams
  {
  	//ici vous devez mettre quelques paramètres tels que :
  	public:
		SetUpParams ();
		~SetUpParams();
		SetUpParams(int indep_runs,int nb_evol_steps,int pop_size,int sol_size, int max ,int numOfinitialImperialists , int numOfcountries /*, double impCost*/);

 		friend ostream& operator<< (ostream& os, const SetUpParams& setup);
		friend istream& operator>> (istream& is, SetUpParams& setup);
       
        void independent_runs(const unsigned int val);
		void nb_evolution_steps(const unsigned int val);
		void population_size(const unsigned int val);
		void solution_size(const unsigned int val);
		void maxCost(const unsigned int val);
        void numOfinitialImperialists(const unsigned int val);
        void numOfcountries(const unsigned int val);
        
		const unsigned int   independent_runs() const;
		const unsigned int   nb_evolution_steps() const;
		const unsigned int   population_size() const;
		const unsigned int   solution_size() const;
		const unsigned int   maxCost()const;
        const unsigned int   numOfinitialImperialists()const;
        const unsigned int   numOfcountries()const;
		
	private:
		unsigned int   _independent_runs;         //number of independent runs
		unsigned int   _nb_evolution_steps;      // number of iterations per run
		unsigned int   _population_size;   		// number of solutions in the population
		unsigned int   _solution_size;	       // size of each particle
		unsigned int   _maxCost;              //le max de cost
        unsigned int   _numOfinitialImperialists;
        unsigned int   _numOfcountries;
        unsigned int   _numOfDecades ;

        double zeta = 0.02; // Total Cost of Empire = Cost of Imperialist + Zeta * mean(Cost of All Colonies)
        int numOfCountries = 50; // Number of initial countries
     	int numOfInitialImperialists = 6;      		// Number of initial imperialists
	    int numOfAllColonies = numOfCountries - numOfInitialImperialists;
	    double revolutionRate = 0.1;               	// Revolution is the process in which the socio-political characteristics of a country change suddenly
	    double assimilationCoefficient = 2;        	// In the original paper assimilation coefficient is shown by "beta"
	    double assimilationAngleCoefficient = .5; 	// In the original paper assimilation angle coefficient is shown by "gama"		
  };
  //=======================================================================

  
  class MyAlgorithm
  {
    private:

		double dampRatio = 0.99; // The damp ratio
		bool stopIfJustOneEmpire = false;  // Use "true" to stop the algorithm when just one empire is remaining. Use "false" to continue the algorithm
		double unitingThreshold = 0.02;  // The percent of search space size, which enables the uniting process of two empires
		int numOfDecades = 10000;	// Number of decades (generations)
        
		srand(unsigned int seed); 
		Solution* fitnessFunc;
        int problemDimension ;
        vector<double> minBounds;	// Minimum bounds
        vector<double> maxBounds;
        vector<double> initialCosts;//le cout du pays initiale
        vector<vector<double> > initialcountries; //the initiale countries withe theirs countries
        vector<vector<double> > bestDecadePosition; // The best found position for each decade
        vector<double> minimumCost;// le cout minimum pour chaque  decennie  = new double[numOfDecades];
        vector<double> meanCost; //le cout moyenne de chaque décennie
        vector<double> searchSpaceSize;	//chercher la taille entre le min et le maxx du limite 
          
          
		vector<Solution*> _solutions;     // individuals in population
		vector<Problem >empireList;//liste of empire (la taille a initialiser par new Empire[numOfInitialImperialists]	
        Problem& _pbm;
        Solution& _solution;
        
        //vector<struct particle> _fitness_values;
        //const SetUpParams& _setup;
        //const Solution& _fitness;//Object fitness de type solution
        //unsigned int _upper_cost,_lower_cost; // lower and upper fitness of individuals in populatio   double[][];
    protected:
    	long seed = millis.count();
        double runICA(int maxEvals);
        double generateNewCountries(int numberOfCountries, int dimension, 
        vector <double> minVector, vector <double> maxVector, int rand);
	
    public:
		MyAlgorithm(const Problem& pbm);/*const SetUpParams& setup*/
		~MyAlgorithm();
		double getCountriesCosts(vector<vector<double> > countriesArray);
		void sortArray(vector<double> arrayToSort, vector<vector<double> >matchingArray);
        void createInitialEmpires();
        void assimilateColonies(Problem* theEmpire);
        void revolveColonies(Problem theProblem);
        void possesEmpire(Solution * theEmpire);
        void uniteSimilarEmpires();
        double getColonyCostsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd);
        double getColonyPositionOfUnitedEmpire(int betterEmpireInd,int worseEmpireInd);
        void  imperialisticCompetition();
        double removeColonyPosition(vector< vector<double> > colonyPositions, int indexToRemove);
        double removeColonyCost(vector<double> colonyCosts, int indexToRemove);
        double concatenatePositions(vector <vector<double> > positions1, vector <double> position2);
        double concatenateCots(vector<double> costs1, double costs);
        void deleteAnEmpire(int indexToDelete);
        int selectAnEmpire(vector<double> probability);
        void  reset();
        string getDetails();
        string getName();	
		//friend ostream& operator<< (ostream& os, const MyAlgorithm& myAlgo);
		//friend istream& operator>> (istream& is, MyAlgorithm& myAlgo);
		//MyAlgorithm& operator= (const MyAlgorithm& myAlgo);
		//const SetUpParams& setup() const;
	  	//void initialize();
	  	//void evaluate();
	  	//const vector<Solution*>& solutions() const;
	  	//unsigned int upper_cost() const;
		//unsigned int lower_cost() const;
		//Solution& solution(const unsigned int index) const;
        //vector<struct particle>&  fitness_values();
		//double fitness(const unsigned int index) const;		 
		//double best_cost() const;
		//double worst_cost() const;
		//Solution& best_solution() const;
		//Solution& worst_solution() const;	 
		//void evolution(int iter); /*makes an evolution step*/

  };
 
  class Utils {
        public:
        	 Utils();
        	 int getMaxIndex(vector <double> vector);
        	 int getMinIndex(vector <double> vector);
        	 double getMean(vector <double> vector);
			 double getNorm(vector <double> vector);
			 double getSum(vector <double> vector);
			 int getSum(vector <int> vector);
			 double max(vector <vector<double> > array1, vector <vector<double> > array2);
			 double min(vector <vector<double> > array1, vector <vector<double> > array2);
			 int randperm(int n, Random r);
			 double repmat(vector <double> pattern,int n);
			 double extractArrayRange(vector <vector<double> > array, int startIndex, int endIndex);
			 double extractGivenArrayParts(vector <vector<double> > array, vector <int> selectedIndexes);
             double extractGivenArrayParts(vector <double> array, vector <int> selectedIndexes);
			 void printArray(string arrayName, vector <double> array);
			 void printArray(string arrayName, vector <vector<double> > array);
		   	 void printArray(string arrayName, vector <int> array);
			 void printProblem(Problem problem, int problemIndex);
			 int getTotalColoniesCount(vector <Problem> problemsList);

        private:
        	Utils* utils;
            
        };

#endif
