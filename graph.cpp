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
	int numPersons;
	int numTrips;

public:

	Graph(int x, int y)
	{
		numPersons = x;
        numTrips = y;
		neighbours = VectorOfSets(x + y + 2, set <WeightedEdge>());
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
		return numPersons + numTrips + 2;
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
		int index = 0;
		float acvalue;
		for (int i = 0; i < numPersons + numTrips + 2; ++i) {
            acvalue = 0.0;
			for (int j = 0; j < Cols; ++j){
				cin >> value;
				if(value > 0) {
                        acvalue += value;
                        addEdge(i + 1,numPersons + index,value);
                        addEdge(numPersons + index, numPersons + numTrips + 1, 3.0); //Es siempre 3???
                        ++index;
				}
			}
			addEdge(0, i + 1, acvalue); //Esta bien esto como peso?
		}
	}

	void printgraph()
	{
		for (int i = 0; i < numPersons + numTrips + 2; ++i)
		{
			cout << "----------------------------" << i <<"----------------------------" << endl;
			for (set<WeightedEdge>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << "neighbour: " << (*it).neighbour << " weight: " << (*it).weight << endl;

			cout<<endl;
		}
	}



};
