#include "algorithm.cpp"


int main() {
	int n, m, value;
	cin>> n >> m;
	Graph G = *new Graph(n);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			cin>>value;
			if(value > 0)G.addEdge(i,j,value);
		}	
	}
	G.printgraph();
}	
