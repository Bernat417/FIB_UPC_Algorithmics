#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector <  set<float>  > VectorOfSets;

class Graph

{

private:

	VectorOfSets neighbours;
	//Necesitamos una graph de capacidades ademas de la de vecinos.
	//Ademas de los correspondientes getters y setters.

public:
	int Rows, Cols;

	Graph(float x, float y)
	{
		Rows = x;
		Cols = y;
		neighbours = VectorOfSets(x, set <float>());
	}

	void addEdge(float x, float y, float weight)
	{
		neighbours[x].insert(weight);
	}

	bool conected(float x, float y)
	{
		return neighbours[x].find(y) == neighbours[x].end();
	}

	float weight(float x, float y)
	{
		return *(neighbours[x].find(y));
	}

	float size()
	{
		return Rows;
	}

	vector<float> getNeighbours(int x)
	{
		vector <float> v (neighbours[x].size());
		int i = 0;
		for (set<float>::iterator it = neighbours[x].begin(); it!= neighbours[x].end(); ++it)
		{
			v[i] = *it;
			++i;
		}
	}

	void readGraph()
	{
		float value;
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
			for (set<float>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << *it <<" ";
		
			cout<<endl;
		}
	}

};
