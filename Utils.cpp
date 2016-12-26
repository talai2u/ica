#include <limits>
#include <math.h>
#include <Utils>

 Utils::Utils(){}
 int Utils::getMaxIndex(vector <double> vector)
	{
       const double max = -std::numeric_limits<double>::min();
		int i;
		int bestIndex = 0;
		for(i=0; i<vector.size(); i++) 
		{
			if(vector[i] > max)
			{
				max = vector[i];
				bestIndex = i;
			}
		}
		return bestIndex;
	}
	
	int Utils::getMinIndex(vector <double> vector)
	{
        const double min = -std::numeric_limits<double>::max();
		int i;
		int bestIndex = 0;
		for(i=0; i<vector.size(); i++) 
		{
			if(vector[i] < min)
			{
				min = vector[i];
				bestIndex = i;
			}
		}
		return bestIndex;
	}
	double Utils::getMean(vector <double> vector) 
	{
		double sum = 0;
		for (int i=0; i<vector.size(); i++) 
		{
			sum += vector[i];
		}
		return sum / vector.size();
	}
	double Utils::getNorm(vector <double> vector) 
	{
		double sum = 0;		
		for(int i=0; i<vector.size(); i++)
		{
			sum = sum + pow(vector[i],2);
		}
		return sqrt(sum);
	}
	double Utils::getSum(vector <double> vector)
	{
		double sum = 0;
		for (double i : vector) 
		{
			sum += i;
		}
		return sum;
	}
  int Utils::getSum(vector <int> vector)
	{
		int sum = 0;
		for (int i : vector) 
		{
			sum += i;
		}
		return sum;
	}
    double Utils::max(vector <vector<double> > array1, vector <vector<double> > array2) 
	{
	    vector <vector<double> > maxArray (array1.size(), vector<double>(array1[0].size()));

		for(int i=0; i<array1.size(); i++)
		{
			for(int j=0; j<array1[0].size(); j++)
			{
				maxArray[i][j] = max(array1[i][j], array2[i][j]);
			}
		}
		return maxArray;
	}
    double Utils::min(vector <vector<double> > array1, vector <vector<double> > array2) 
	{
		vector <vector<double> > minArray (array1.size(), vector<double>(array1[0].size()));
		for(int i=0; i<array1.size(); i++)
		{
			for(int j=0; j<array1[0].size(); j++)
			{
				minArray[i][j] = min(array1[i][j], array2[i][j]);
			}
		}
		return minArray;
	}
	int Utils::randperm(int n, Random r) 
	{
		std::vector<std::string> nVector;
		for(int i=0; i<n; i++)
		{
			nVector.push_back(i);
		}
		  vector <int> outputVector(n.size());
		int outputIndex = 0;

		while(nVector.size()>0)
		{
			int position = r.next(nVector.size());
			outputVector[outputIndex] = nVector.get(position);
			outputIndex++;
			nVector.remove(position);
		}

		return outputVector;
	}
	double Utils::repmat(vector <double> pattern,int n) 
	{
        vector <vector<double> > outputArray (n, vector<double>(pattern.size()));

		for(int i=0; i<n; i++)
		{
			outputArray[i] = pattern;
		}
		return outputArray;
	}
	double Utils::extractArrayRange(vector <vector<double> > array, int startIndex, int endIndex)
	{
		vector <vector<double> > arrayExtract (endIndex-startIndex, vector<double>(array[0].size()));
		int newIndex = 0;
		for(int i=startIndex; i<endIndex ; i++)
		{
			arrayExtract[newIndex] = array[i];
			newIndex++;
		}
		return arrayExtract;
	}
	double Utils::extractGivenArrayParts(vector <vector<double> > array, vector <int> selectedIndexes) 
	{
		vector <vector<double> > arrayExtract (selectedIndexes.size(), vector<double>(array[0].size()));
		int index;
		for(int i=0; i<selectedIndexes.size(); i++)
		{
			index = selectedIndexes[i];
			arrayExtract[i] = array[index];
		}
		return arrayExtract;
	}
    double Utils::extractGivenArrayParts(vector <double> array, vector <int> selectedIndexes) 
	{	
	    vector <double> arrayExtract(selectedIndexes.size());
		int index;
		for(int i=0; i<selectedIndexes.size(); i++)
		{
			index = selectedIndexes[i];
			arrayExtract[i] = array[index];
		}
		return arrayExtract;
	}
	 void Utils::printArray(String arrayName, vector <double> array)
	{
		cout <<arrayName<<": "<<toString(array);
	}
	void Utils::printArray(String arrayName, vector <vector<double> > array)
	{
		for(int i=0; i<array.size(); i++)
		{
					cout <<arrayName<<"["<<i<<"]: "<<toString(array[i]);
		}
	}
	void Utils::printArray(String arrayName, vector <int> array) 
	{
     	cout <<arrayName<<":"<<toString(array);
	}	
	 void Utils::printEmpire(Empire empire, int empireIndex) 
	    {cout << "Empire "  <<empireIndex<<;
        cout << "Number of colonies: "  <<empire.getColoniesCost().size()<<;
        cout << "imperialistPosition: "  <<empire.getImperialistPosition()<<;
        cout << "imperialistCost: "  <<empire.getImperialistCost()<<;
        cout << "coloniesPosition: "  <<empire.getColoniesPosition()<<;
        cout << "coloniesCost: "  <<empire.getColoniesCost()<<;
        cout << "totalCost: "  <<empire.getTotalCost()<<;
	}
	int Utils::getTotalColoniesCount(vector <Empire> empiresList) 
	{
		int currentNumOfColonies = 0;
		for(int i=0; i<empiresList.size(); i++)
		{
			currentNumOfColonies = currentNumOfColonies + empiresList[i].getColoniesPosition().size();
		}
		return currentNumOfColonies;
	}

	
