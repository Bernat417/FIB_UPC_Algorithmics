#include "algorithm.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n,m);
	G.readGraph(m);
	G.printgraph();
	Algorithm A = *new Algorithm();
	float f = 0.0;
	Matrix Res = A.edmonskarp(G,f);
	for (int i = 0; i < Res.size(); ++i){
		for (int j = 0; j < Res.size(); ++j){
			cout<<Res[i][j]<<" ";
		}
		cout<<endl;
	}
}
