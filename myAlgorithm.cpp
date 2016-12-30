#include <math.h> 
#include<Random>
#include <algorithm>
#include <ctime>
#include"myAlgorithm.h"
#include"Utils.cpp"
#include"Solution.cpp"
#include"Problem.cpp"

using namespace System;
using namespace std ;

  MyAlgorithm::MyAlgorithm(const Problem& pbm)
        :minbound{pbm.LowerLimit()},
        maxbound{pbm.UpperLimit()},
        problemDimension{pbm.Dimension()}
        _pbm{pbm}
     {}

  double MyAlgorithm::runICA(int maxEvals){
    
    // Initialize variables
    bestDecadePosition.resize(_numOfDecades);
    for (int i = 0; i < _numOfDecades; ++i)
        bestDecadePosition[i].resize(problemDimension);
    
    searchSpaceSize.resize(problemDimension);
    
    // Compute the problem search space, between the min and max bounds
    for(int i=0; i<problemDimension; i++){
        searchSpaceSize[i] = maxBounds[i] - minBounds[i];
    }
    
    // Create an initial population of individuals (countries)
    initialCountries = generateNewCountries(numOfCountries, problemDimension, minBounds, maxBounds, r);
    
    // Compute the cost of each country: the lesser the cost, the more powerful the country is
    initialCosts = getCountriesCosts(initialCountries);
    
    // Sort the costs and the corresponding countries in assending order. The best countries will be in higher places.
    // @todo Ã  complÃ©ter ..
    sortArray(initialCosts, initialCountries);
    
    // Create the initial empires
    createInitialEmpires();
		
       
}


/** Generates new countries
 * @param numberOfCountries the number of countries to generate
 * @param dimension the dimension of each country
 * @param minVector the minimum values for each dimension 
 * @param maxVector the maximum values for each dimension
 * @param rand a random number generator
 * @return an array with the new countries positions **/
//
double MyAlgorithm::generateNewCountries(int numberOfCountries, int dimension, vector <double> minVector, vector <double> maxVector, Random rand)
{
    
    vector <vector<double> > countriesArray(numberOfCountries, vector<int>(dimension));
    for(int i=0; i<numberOfCountries; i++)
    {
        for(int j=0; j<dimension; j++)
        {
            countriesArray[i][j] = (maxVector[j] - minVector[j]) * rand.nextDouble() + minVector[j];
        }
    }
    return countriesArray;
    
}

/**
 * Returns a vector with the cost of all countries computed according to their position
 * @param numberOfCountries the number of countries
 * @param countriesArray
 * @return a vector with the costs of all countries
 */
double MyAlgorithm::getCountriesCosts(vector<vector<double> > countriesArray)
{
    vector <double> costsVector(countriesArray.size());
    for(int i=0; i<countriesArray.size(); i++)
    {   
        
        costsVector[i] = _solution.getFitnessValue(countriesArray[i]);
    }
    return costsVector;
}


/**
 * Sorts an array according to its values and sorts another array in the same order
 * The lowest value is put first
 * @param arrayToSort the array to sort according to its values
 * @param matchingArray the array that should be sorted according to the first one
 */
void MyAlgorithm::sortArray(vector<double> arrayToSort, vector<vector<double> >matchingArray)
{
    // Create an index array
    vector<int> sortOrder(arrayToSort.size());
    for(int i=0; i<sortOrder.size(); i++)
    {
        sortOrder[i] = i;
    }
    
     // Sort the array using the index array, thanks to a custom comparator
     // @todo convert to c++ : Arrays.sort(sortOrder,new Comparator<Integer>() .... 
    
    // Create copies of the arrays
    vector<double> arrayToSortCopy = arrayToSort;
    vector<vector<double> > matchingArrayCopy = matchingArray;
    
    // Output the values using the sorted indexes
    for(int i=0;i<sortOrder.length;i++)
    {
        initialCosts[i] = arrayToSortCopy[sortOrder[i]];
        initialCountries[i] = matchingArrayCopy[sortOrder[i]];
    }
    
}
    

/**
 * Generates the initial empires
*/
void MyAlgorithm::createInitialEmpires()
{
    // Extract the best countries to create empires
    //  utils.extractArray  a verifier dans Utilis
    vector<double> allImperialistsPosition = utils.extractArrayRange(initialCountries, 0, numOfInitialImperialists);
    
    vector<double> allImperialistsCost(numOfInitialImperialists);
    // copy est l'équivalent de arraycopy in  c++ , a verifier !!!
    //System.arraycopy(initialCosts, 0, allImperialistsCost, 0, numOfInitialImperialists);
       Array::Copy(initialCosts, 0, allImperialistsCost, 0, numOfInitialImperialists);
    
    // Extract the rest to create colonies
    vector<double> allColoniesPosition = utils.extractArrayRange(initialCountries, numOfInitialImperialists, initialCountries.size());
    
    // Extract their costs
    vector<double> allColoniesCost(initialCosts.size()-numOfInitialImperialists); 
    //System.arraycopy(initialCosts, numOfInitialImperialists, allColoniesCost, 0, initialCosts.length-numOfInitialImperialists);	
    Array::Copy(initialCosts, numOfInitialImperialists, allColoniesCost, 0, initialCosts.size()-numOfInitialImperialists);
    
	// Compute the power of imperialists
    vector<double> allImperialistsPower(numOfInitialImperialists);
    
    
    
    if(allImperialistsCost[utils.getMaxIndex(allImperialistsCost)]>0)
    {
        for(int i=0; i<allImperialistsCost.size(); i++)
        {
            allImperialistsPower[i] = 1.3 * allImperialistsCost[utils.getMaxIndex(allImperialistsCost)] - allImperialistsCost[i];
        }
    } else
    {
        for(int i=0; i<allImperialistsCost.size(); i++)
        {
            allImperialistsPower[i] = 0.7 * allImperialistsCost[utils.getMaxIndex(allImperialistsCost)] - allImperialistsCost[i];
        }
    }
    
    // Set the number of colonies for the imperialists 
    vector<int> allImperialistNumOfColonies(numOfInitialImperialists);
    
    for(int i=0; i<allImperialistsPower.size(); i++)
    {   
        
        allImperialistNumOfColonies[i] = (int) round(allImperialistsPower[i]/utils.getSum(allImperialistsPower) * numOfAllColonies);
    }
    
    allImperialistNumOfColonies[allImperialistNumOfColonies.size()-1] = 
 
    // Arrays.copyOfRange il est faite dans les autres exemple avec une boucle mais 
	 //dans ce cas on peux pas faire une for dans la methode getsum , a vérifier !!!!!!
    std::max(   
                numOfAllColonies - 
                utils.getSum(Arrays.copyOfRange(allImperialistNumOfColonies, 0, allImperialistNumOfColonies.size()-1)),
                0
        );
    
    // Initialize the empires
    for(int i=0; i<numOfInitialImperialists; i++)
    {
        empiresList[i] = new Solution(problemDimension);
    }
    
    // Create a random permutation of integers
    
    vector<int> randomIndex = utils.randperm(numOfAllColonies, r);
   
    // Create the empires and attribute them their colonies
    for(int i=0; i<numOfInitialImperialists; i++)
    {   
        
        //vector<int> R = Arrays.copyOfRange(randomIndex, 0, allImperialistNumOfColonies[i]);
         /// transformation de copyOfRange a verifier !!!
         vector<int> R;
         for(int i=0;i<allImperialistNumOfColonies.size();i++)
	    {
		  R.pushback(randomIndex[i]);
	    }
		  
        // @todo init to c++
        empiresList[i].init(R.size());
        
        //randomIndex = Arrays.copyOfRange(randomIndex, allImperialistNumOfColonies[i], randomIndex.size());
         for(int i=0;i<allImperialistNumOfColonies.size();i++)
	    {
		  	randomIndex.pushback(randomIndex[allImperialistNumOfColonies+i]);
		}
           
        empiresList[i].setImperialistPosition(allImperialistsPosition[i]);
        empiresList[i].setImperialistCost(allImperialistsCost[i]);
        empiresList[i].setColoniesPosition(utils.extractGivenArrayParts(allColoniesPosition, R));
        empiresList[i].setColoniesCost(utils.extractGivenArrayParts(allColoniesCost, R));
        empiresList[i].setTotalCost(empiresList[i].getImperialistCost() + zeta * utils.getMean(empiresList[i].getColoniesCost()));

    }

}

	/**
	 * Assimilates the colonies of an empire: move their positions
	 * @param theEmpire
	 */
//Assimilates the colonies of an empire: move their positions //Assimile les colonie d'un empire: deplacent leur position

 void MyAlgorithm::assimilateColonies(Problem* theEmpire)
{
			// Get the number of colonies of the empire // obtenir le nombre de colonie de l'empire

	int numOfColonies = theEmpire.getColoniesPosition().size;
	// Create an array containing the distance between the imperialist and the colonies//creer un tableu contenant la distance entre imperialiste et les colonie
	vector <vector<double> > repmatArray= utils.repmat(theEmpire.getImperialistPosition(),numOfColonies);		
    vector <vector<double> > array(numOfColonies, vector<int>(problemDimension));
    for(int i=0; i<numOfColonies; i++)
		{
			for(int j=0; j<problemDimension; j++)
			{
				array[i][j] = repmatArray[i][j] - theEmpire.getColoniesPosition[i][j];
			}
		}
	// Create a new array to store the updated colonies positions//creer un nouveau table pour stocker les position de colonies
		vector <vector<double> > coloniesPosition(numOfColonies, vector<int>(problemDimension));
	//	Fill the array//remplir le tableau
		for(int i=0; i<array.size; i++)
		{
			for(int j=0; j<array[0].size; j++)
			{
				coloniesPosition[i][j] = theEmpire.getColoniesPosition[i][j] + 2 * assimilationCoefficient * r.nextDouble() * array[i][j];
			}
		}
		// Update the positions//mettre a jour les position
	theEmpire.setColoniesPosition(coloniesPosition);
	// Bound the values with the min and max bounds//limite les valeur avec les limite min et max
	vector <vector<double> > minVarMatrix=utils.repmat(minBounds,numOfColonies);
	vector <vector<double> > maxVarMatrix = utils.repmat(maxBounds,numOfColonies);
	theEmpire.setColoniesPosition(utils.max(theEmpire.getColoniesPosition(),minVarMatrix));
	theEmpire.setColoniesPosition(utils.min(theEmpire.getColoniesPosition(),maxVarMatrix));

}
 
/**
	 * Make colonies of an empire revolve.
	 * This is equivalent to a perturbation which avoid getting stuck 
	 * into local minima.
	 * @param theEmpire to revolve
	 */
	 ///attetion il existe pas une classe empire = solution 
  void  MyAlgorithm::revolveColonies(Empire theEmpire)
	{
		// Get the number of colonies to revolve
		//a verefier !!!!!!!!!!!!!!!
		int numOfRevolvingColonies = (int) Math.round((revolutionRate * theEmpire.getColoniesCost().size()));

		// Create a new array with new random positions for the revolving colonies
		vector<vector<double>> revolvedPosition = generateNewCountries(numOfRevolvingColonies, problemDimension, minBounds, maxBounds, r);
		
		// Generate a vector with integer values in a random order
		// copyOfRange is for copying array arr1 to arr2 with range from index 2 to 6
		vector<int> R = utils.randperm(theEmpire.getColoniesCost().size(), r);
		//R = Arrays.copyOfRange(R, 0, numOfRevolvingColonies);
		for(int i=0;i<numOfRevolvingColonies;i++)
	     {
	        R.pushback(R[i]);
	     }

		// Update the positions of the revolved colonies of the empire
		for(int i=0; i<R.size(); i++)
		{
			theEmpire.setColonyPosition(R[i], revolvedPosition[i]);
		}
	}
	
   	/**
	 * Can make a colony become the imperialist 
	 * if it is more powerful than the imperialist.
	 * @param theEmpire
	 */
  void  myAlgorithme::possesEmpire(Solution * theEmpire)
   {    
         // Get the costs of the colonies
       vector<double> coloniesCost.resize(theEmpire.getColoniesCost());
       
        // Get the cost of the best colony (the lowest cost)
       	int bestColonyInd = utils.getMinIndex(coloniesCost);
		double minColoniesCost = coloniesCost[bestColonyInd];
        if (minColoniesCost<theEmpire.getImperalistCost())
        {   
           // Backup the position and cost of the former imperialist
            vector<double> oldImperialistpositio.resize(theEmpire.getImperialistPosition());
            double oldImperialistCost = theEmpire.getImperialistCost();
            // Update the position and cost of the imperialist with the ones of the colony
			theEmpire.setImperialistPosition(theEmpire.getColoniesPosition()[bestColonyInd]);
			theEmpire.setImperialistCost(theEmpire.getColoniesCost()[bestColonyInd]);

			// Update the position and cost of the former colony with the ones of the former imperialist
			theEmpire.setColonyPosition(bestColonyInd, oldImperialistPosition);
			theEmpire.setColonyCost(bestColonyInd, oldImperialistCost);
        }
        
   }
  
  /**
	 * Unites imperialists that are close to each other
	 */
 void MyAlgorithm::uniteSimilarEmpires()
	{
		// Get the threshold distance between two empires
		double thresholdDistance = unitingThreshold * utils.getNorm(searchSpaceSize);

		// Get the number of empires
		int numOfEmpires = empiresList.size();

		// Compare each empire with the other ones
		for(int i=0; i<(numOfEmpires-1); i++)
		{
			for(int j=i+1; j<numOfEmpires; j++)
			{
				// Compute the distance between the two empires i and j
				 vector<double> distanceVector(empiresList[i].getImperialistPosition().size());
				for(int k=0; k<empiresList[i].getImperialistPosition().size(); k++)
				{
					distanceVector[k] = empiresList[i].getImperialistPosition()[k] - empiresList[j].getImperialistPosition()[k];
				}
				double distance = utils.getNorm(distanceVector);

				// If the empires are too close
				if(distance<=thresholdDistance)
				{
					// Get the best and worst empires of the two
					int betterEmpireInd;
					int worseEmpireInd;
					if(empiresList[i].getImperialistCost() < empiresList[j].getImperialistCost())
					{
						betterEmpireInd=i;
						worseEmpireInd=j;
					}
					else
					{
						betterEmpireInd=j;
						worseEmpireInd=i;
					}

					// Update the positions
					vector<vector<double>> newColoniesPosition  = getColonyPositionsOfUnitedEmpire(betterEmpireInd, worseEmpireInd);
					empiresList[betterEmpireInd].setColoniesPosition(newColoniesPosition);

					// Update the costs
					vector<double> newColoniesCost = getColonyCostsOfUnitedEmpire(betterEmpireInd, worseEmpireInd);
					empiresList[betterEmpireInd].setColoniesCost(newColoniesCost);

					// Update the total cost of the united empire                                     
					empiresList[betterEmpireInd].setTotalCost(
							empiresList[betterEmpireInd].getImperialistCost() +
							zeta * utils.getMean(empiresList[betterEmpireInd].getColoniesCost())
					);

					// Update the empires list
					deleteAnEmpire(worseEmpireInd);
					//System.out.println("New number of empires: " + empiresList.length);

					return;
				}

			}
		}  
	}

/**
	 * Returns the costs of the colonies of the united empire (after two empires merge) 
	 * @param betterEmpireInd the best empire
	 * @param worseEmpireInd the worst empire
	 * @return the corresponding colony costs
	 */
  double myAlgorithme::getColonyCostsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd)
  {
      int newColoniesCount=empireList[betterEmpireInd].getColoniesCost().size()+1+empireList[worseEmpireInd].getColoniesCost().size();
      vector <double>newColoniesCost(vector<double>newColoniesCount);
      int i ;
      for(i=0;i<empireList[betterEmpireInd].getColoniesCost().size();i++) //danger//
      {
          newColoniesCost[i]=empireList[betterEmpireInd].getColoniesCost(i);
          
      }
      newColonies[i]= empireList[worseEmpireInd].getImperialistCost();
      int i2;
      for(i2=i+1; i2<newColoniesCount;i2++)
      {
          newColoniesCost[i2]=empireList[worseEmpireInd].getColoniesCost(i2-empireList[betterEmpireInd].getColoniesCost().size()-1);
          
      }
      return newColoniesCost; //mise a jour du Costs
  }

	/**
	 * Returns the positions of the colonies of the united empire (after two empires merge) 
	 * @param betterEmpireInd the best empire
	 * @param worseEmpireInd the worst empire
	 * @return the corresponding colony positions
	 */
  double myAlgorithme :: getColonyPositionOfUnitedEmpire(int betterEmpireInd,int worseEmpireInd)
  {
      int newSize = empiresList[betterEmpireInd].getColoniesPosition().size()+ 1 + empiresList[worseEmpireInd].getColoniesPositio().size();
      //double[][] newColoniesPosition = new double[newSize][problemDimension];
      vector<vector<double>> newColoniesPosition(newSize,problemDimension);
      int i;
      for (i=0;i<empireList[betterEmpireInd].getColoniesPosition().size();i++)
      {
          newColoniesPosition[i]=empireList[betterEmpireInd].getColoniesPosition(i);
          
      }
      newColoniesPosition[i]=empireList[betterEmpireInd].getColoniesPosition(i);
      int i2;
      for(i2=i+1;i2<newSize;i2++)
      {
          newColoniesPosition[i2]=empireList[worseEmpireInd].getColoniesPosition(i2-empireList[betterEmpireInd].getColoniesPosition().size()-1);
          
      }
          return newColoniesPosition;//mise a jour de la position
  }	
  
  /**
	 * Runs the competition between empires
	 */
	void  MyAlgorithm::imperialisticCompetition()
	{
		// Generate a random number, and return if this number is too high
		double rand = r.nextDouble();
		if(rand > .11)
		{
			return;
		}
			
		// Idem if their is only one empire
		if(empiresList.size()<=1)
		{
			return;
		}
		
		// Get the total cost of each empire
		//attetion la methode de getotalcost se trouve dans la calsse empire de java !!!!!
		//utils.printArray("totalCosts", totalCosts);
		vector <double> totalCosts(empiresList.size());
	
		for(int i=0; i<empiresList.size(); i++)
		{
			totalCosts[i] = empiresList[i].getTotalCost();
		}
	
		
		// Get the weakest empire (the one with the highest cost) and its cost
		int weakestEmpireInd = utils.getMaxIndex(totalCosts);//getmaxindex se trouve dans la classe utils 
		double maxTotalCost = totalCosts[weakestEmpireInd]; 
		
		// Get the power of each empire
		vector <double> totalPowers(empiresList.size());
		
		for(int i=0; i<empiresList.size(); i++)
		{
			totalPowers[i] = maxTotalCost - totalCosts[i];
		}
		//utils.printArray("totalPowers", totalPowers);
		
		// Get the possession probability of each empire
		//utils.printArray("possessionProbability", possessionProbability);
		 vector <double> possessionProbability(empiresList.size());
	
		for(int i=0; i<empiresList.size(); i++)
		{
			possessionProbability[i] = totalPowers[i] / utils.getSum(totalPowers);//getsum se trouve dans la classe utils 
		}
		
		// Select an empire according to their probabilities
		int selectedEmpireInd = selectAnEmpire(possessionProbability);
		//System.out.println("selectedind: " + selectedEmpireInd);
	
		// Generate a random integer
		int numOfColoniesOfWeakestEmpire = empiresList[weakestEmpireInd].getColoniesCost().size();
		int indexOfSelectedColony = r.nextInt(numOfColoniesOfWeakestEmpire); //cherche nextint en c++
		
		// Update the positions of the colonies of the selected empire 
		// by adding the position of the randomly selected colony of the weakest empire
		//setcoloniesposition getColoniesPosition est fait dans classe solution 
		empiresList[selectedEmpireInd].setColoniesPosition(	
				concatenatePositions(
						empiresList[selectedEmpireInd].getColoniesPosition(), 
						empiresList[weakestEmpireInd].getColoniesPosition()[indexOfSelectedColony]
				)
		);
		
		// Idem for the costs
		// setColoniesCost et est fait dans classe solution 
		empiresList[selectedEmpireInd].setColoniesCost( 
				concatenateCosts(
						empiresList[selectedEmpireInd].getColoniesCost(), 
						empiresList[weakestEmpireInd].getColoniesCost()[indexOfSelectedColony]
				) 
		);
		
		
		// Update the positions of the colonies of the weakest empire 
		// by removing the position of the randomly selected colony of the empire
		empiresList[weakestEmpireInd].setColoniesPosition( 
				removeColonyPosition(empiresList[weakestEmpireInd].getColoniesPosition(), indexOfSelectedColony) 
		);
		
		// Idem for the costs
		empiresList[weakestEmpireInd].setColoniesCost( 
				removeColonyCost(empiresList[weakestEmpireInd].getColoniesCost(), indexOfSelectedColony) 
		);
		
		// Get the number of colonies of the weakest empire
		numOfColoniesOfWeakestEmpire = empiresList[weakestEmpireInd].getColoniesCost().size();
		
		
		// If it has not more than 1 colony, then make it disapear/collapse
		// It is then absorbed by the selected empire
		if(numOfColoniesOfWeakestEmpire<=1)
		{
			// Update the positions of the colonies by adding the collapsed imperialist
			empiresList[selectedEmpireInd].setColoniesPosition( 
					concatenatePositions(
							empiresList[selectedEmpireInd].getColoniesPosition(), 
							empiresList[weakestEmpireInd].getImperialistPosition()
					) 
			);

			// Idem for the costs
			empiresList[selectedEmpireInd].setColoniesCost( 
					concatenateCosts(
							empiresList[selectedEmpireInd].getColoniesCost(), 
							empiresList[weakestEmpireInd].getImperialistCost()
					) 
			);

			// Erase the collapsed empire from the empires list
			deleteAnEmpire(weakestEmpireInd);
			//System.out.println("An empire has collapsed");
			//System.out.println("New number of empires: " + empiresList.length);
		}
	}
	
 	/**
	 * Removes a position from the colony positions array
	 * @param colonyPositions
	 * @param indexToRemove
	 * @return the updated positions
	 */
  //Removes a position from the colony positions array
  double myAlgorithme ::removeColonyPosition(vector<vector<double>> colonyPositions, int indexToRemove)
  {
      vector<vector<double>> newColonyPostions(colonyPositions.size()-1,colonyPositions[0].size());
      for(int i=0;i<indexToRemove;i++)
      {
          newcolonyPositions [i]=colonyPositions[i];
      }
      for(int j=indexToRemove;j<newColonyPositions.size();j++)
      {
          newcolonyPositions[j]=colonyPositions[j+1];
      }    
    return newColonyPositions;//mise a jour de la position
 }

/**
	 * Removes a position from the colony costs vector
	 * @param colonyCosts
	 * @param indexToRemove
	 * @return the updated costs vector
	 //Removes a position from the colony costs vector
	 */
  double myAlgorithme ::removeColonyCost(vector<double> colonyCosts, int indexToRemove)
  {
       vector<double> newColonyCosts(colonyCosts.size()-1);
       for(int i=0 ;i<indexToRemove;i++)
       {
           newColonyCosts[i]=colonyCost[i];
       }
       for(int j=indexToRemove;j<newColonyCosts.size();j++)
       {
           newColonyCosts[j]=colonyCosts[j+1];
       }    
        return newColonyCosts ;
  }
 /**
	 * Concatenates the positions of an empire with an additionnal one
	 * @param positions1 the positions array of the empire
	 * @param position2 the position to add
	 * @return the updated positions
	 */
 double MyAlgorithm::concatenatePositions(vector <vector<double> > positions1, vector <double> position2)
    {
	  	// Create a new array to store the updated positions 
	    vector <vector<double> > newPositions (positions1.size()+1, vector<double>(position1[0].size()));
	    // Add the positions of the existing empire in the array
		int i;
		for(i=0; i<positions1.size(); i++)
		{
			newPositions[i] = positions1[i];
		}

		// Then add the position to add at the end
		newPositions[i] = position2;

		// Return the updated positions
		return newPositions;
	}
	
	/**
	 * Concatenates the costs of an empire with an additionnal one
	 * @param costs1 the costs vector of the empire
	 * @param cost2 the cost to add
	 * @return the updated costs
	 */
  double myAlgorithme:: concatenateCots(vector<double> costs1, double costs)
  {
       
        vector<double> newCosts.resize(costs1.size()+1);// Create a new vector to store the updated costs
       
        int i ; // Add the costs of the existing empire in the array
        for(i=0;i<costs1.size();i++)
        {
            newCosts[i]=costs1[i];
        }
        // Then add the cost to add at the end
        newCosts[i]=costs;
        
        return newCosts;//mise a jour Costs
  }
  
     	/**
	 * Deletes an empire from the empires list
	 * @param indexToDelete
	 */
   void MyAlgorithm::deleteAnEmpire(int indexToDelete)
{
	 // Split the empires list into two sub lists, before and after the empire to remove
	  std::vector<Solution*> empiresList1;
	   std::vector<Solution*> empiresList2;
	 for(int i=0;i<indexToDelete;i++)
	 {
	 	empiresList1.pushback(empiresList[i]);
	 	empiresList2.pushback(empiresList[indexToDelete+i+1]);
	 }
	 
	// Create a new list with the updated size
	 empiresList.resize(empiresList1.size()+empiresList2.size());
	 // Copy the empires of the sub lists into the new one
	 for(int n=0; n<(empiresList1.size + empiresList2.size); n++)
		{
			if(n<empiresList1.size())
			{
				empiresList[n] = empiresList1[n];
			}

			if(n>= empiresList1.size())
			{
				empiresList[n] = empiresList2[n-empiresList1.size()];
			}
		}
	 
}
/**
	 * Selects an empire according to their probabilities 
	 * @param probability the probability vector
	 * @return the selected empire index
	 */
	 int MyAlgorithm::selectAnEmpire(vector<double> probability)
	 { 
	    // Create a vector of random numbers
	 	vector<double> randvector(probability.size()); 
	 	for(int i=0; i<probability.size(); i++)
	 	{
	 	  randVector[i] = rand.nextDouble();	
	 	}
	 	// Substract to each element of this vector the corresponding 
		// value of the probability vector
		vector<double> dVector(probability.size());
	    for(int i=0; i<probability.size(); i++)
	 	{
		   dVector[i] = probability[i] - randVector[i];
		 }
		 
	 	// Return the index of the maximum value of the vector
		return utils.getMaxIndex(dVector);
	 }   
	 
	/**
	 * Resets the variables for the next run
	 */
  void myAlgorithme :: reset() // a verefier !!!!!!
  {
       // r =  rand();
     /*   bestDecadePosition.resize(_numOfDecades);
    for (int i = 0; i < _numOfDecades; ++i)
        bestDecadePosition[i].resize(problemDimension); */
            empiresList.resizeEmpire(numOfInitialImperialists);	// List of Empires
            minimumCost.resize(numOfDecades);	// The minimum cost of each decade
            meanCost.resize(numOfDecades);
        
        
            _Solution.nbEvals = 0;
  }

     
/**
	 * Returns a string with informtion about the algorithm
	 * @return the string
	 */
String MyAlgorithm::getDetails()
{
	return "Imperialist Competitive Algorithm (ICA): " + 
		"as described in: Atashpaz-Gargari, E. and Lucas, C., Imperialist Competitive Algorithm: An Algorithm for Optimization Inspired by Imperialistic Competition, IEEE Congress on Evolutionary Computation, 2007, pp. 4661-4667." +
		" Adapted from: http://www.mathworks.com/matlabcentral/fileexchange/22046-imperialist-competitive-algorithm-ica";
}
  
   
    string MyAlgorithm::getName()
{
	
	return "Imperialist Competitive Algorithm";
	
}




    
