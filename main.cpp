#include "algorithm.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n);
	G.readGraph(m);
	G.printgraph();
}	

