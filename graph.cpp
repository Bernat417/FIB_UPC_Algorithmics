#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector <  set<int>  > VectorOfSets;

class Graph

{

private:

	VectorOfSets neighbours;
	//Necesitamos una graph de capacidades ademas de la de vecinos.
	//Ademas de los correspondientes getters y setters.

public:
	int Rows, Cols;

	Graph(int x, int y)
	{
		Rows = x;
		Cols = y;
		neighbours = VectorOfSets(x, set <int>());
	}

	void addEdge(int x, int y, int weight)
	{
		neighbours[x].insert(weight);
	}

	bool conected(int x, int y)
	{
		return neighbours[x].find(y) == neighbours[x].end();
	}

	int weight(int x, int y)
	{
		return *(neighbours[x].find(y));
	}

	int size()
	{
		return Rows;
	}

	void readGraph()
	{
		int value;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Cols; ++j){
				cin>>value;
				if(value > 0)addEdge(i,j,value);
			}	
		
	}

	void printgraph()
	{
		for (int i = 0; i < Rows; ++i)
		{
			cout << "----------------------------" << i <<"----------------------------" << endl;
			for (set<int>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << *it <<" ";
		
			cout<<endl;
		}
	}

};
