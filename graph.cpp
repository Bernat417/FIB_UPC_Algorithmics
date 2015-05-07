#include <iostream>
#include <vector>

using namespace std;

typedef vector <  vector<int>  > adjacency_Matrix;

class graph
{
private:
	adjacency_Matrix matrix;

public:
	graph(int size)
	{
		matrix = adjacency_Matrix(size, vector <int> (size,0) ) ;
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
	
};
