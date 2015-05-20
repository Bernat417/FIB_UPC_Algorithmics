#include <iostream>
#include <vector>

using namespace std;

typedef vector <  vector<int>  > adjacency_Matrix;

class graph
{
private:
	adjacency_Matrix matrix;
	//Necesitamos una matrix de capacidades ademas de la de vecinos.

public:
	graph(int size, int size2)
	{
		matrix = adjacency_Matrix(size, vector <int> (size2,0) ) ;
	}

	void addEdge(int x, int y, int weight)
	{
		matrix[x][y] = weight;
	}

	bool conected(int x, int y)
	{
		return (matrix[x][y] != 0);
	}

	int weight(int x, int y)
	{
		return matrix[x][y];
	}

	int numfilas()
	{
		return matrix.size();
	}
	
	int numcolumnas()
	{
		return matrix[0].size();
	}
};
