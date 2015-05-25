#include <iostream>
#include <vector>
#include <set>

using namespace std;



class Graph

{

private:
	class WeightedEdge
	{
		public:
			int neighbour;
			float weight;

			WeightedEdge()
			{
				neighbour = weight = 0;
			}

			WeightedEdge(int x, float y)
			{
				neighbour = x;
				weight = y;
			}

			bool operator<(const WeightedEdge& e) const 
			{
   				return neighbour < e.neighbour;  //assume that you compare the record based on a
			}

			bool operator== ( const WeightedEdge &e) 
			{
        		return neighbour == e.neighbour;
			}
	};

	typedef vector <  set<WeightedEdge>  > VectorOfSets;
	VectorOfSets neighbours;
	int numNodes;

public:	

	Graph(float x)
	{
		numNodes = x;
		neighbours = VectorOfSets(x, set <WeightedEdge>());
	}

	void addEdge(int x, int y, float weight)
	{
		neighbours[x].insert(WeightedEdge(y,weight));
	}

	bool conected(int x, int y)
	{
		WeightedEdge e(y,0);
		return neighbours[x].find(e) != neighbours[x].end();
	}

	float weight(int x, int y)
	{
		WeightedEdge e(y,0);
		return (*(neighbours[x].find(e))).weight;
	}

	float size()
	{
		return numNodes;
	}

	vector<WeightedEdge> getNeighbours(int x)
	{
		vector <WeightedEdge> v (neighbours[x].size());
		int i = 0;
		for (set<WeightedEdge>::iterator it = neighbours[x].begin(); it!= neighbours[x].end(); ++it)
		{
			v[i] = WeightedEdge ((*it).neighbour, (*it).weight);
			++i;
		}
		return v;
	}

	void readGraph(int Cols)
	{
		float value;
		for (int i = 0; i < numNodes; ++i)
			for (int j = 0; j < Cols; ++j){
				cin>>value;
				if(value > 0)addEdge(i,j,value);
			}	
		
	}

	void printgraph()
	{
		for (int i = 0; i < numNodes; ++i)
		{
			cout << "----------------------------" << i <<"----------------------------" << endl;
			for (set<WeightedEdge>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << "neighbour: " << (*it).neighbour << " weight: " << (*it).weight << endl;
		
			cout<<endl;
		}
	}



};
