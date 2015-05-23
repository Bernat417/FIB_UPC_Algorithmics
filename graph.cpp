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

	Graph(int size)
	{
		neighbours = VectorOfSets(size, set <int>());
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
		return neighbours.size();
	}

	void printgraph(){
		int n = neighbours.size();
	
		for (int i = 0; i < n; ++i)
		{
			cout << "----------------------------" << i <<"----------------------------" << endl;
			for (set<int>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << *it <<" ";
		
			cout<<endl;
		}
	}

};
