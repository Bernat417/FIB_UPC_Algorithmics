#include "algorithm.cpp"

void printSol (const int& n, const int& m, const Matrix& Res) {
	vector<int> sol(m);
		for (int i = 2; i < n+2; ++i){
			for (int j = n+2; j < m+n+2; ++j){
				if (Res[i][j] == 1) sol[j-(n+2)] = i;
			}
		}
	cout << sol[0]-2;
	for (int i = 1; i < sol.size(); ++i) cout << " " << sol[i]-2;
	cout << endl;
}

int main (int argc, char *argv[]) {
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n,m);
	bool tipoA = G.readGraph(m);
	//G.printgraph();
	Algorithm A = *new Algorithm();
	float f = 0.0;
	Matrix Res;
	if (tipoA) {
		Res = A.edmonskarp(G,f);
		//G.printgraph();
		if (f == m) {
			cout << "A" << endl;
			printSol(n, m, Res);
			return 0;
		}
	}
	G.UpdateGraph1(m);
	//G.printgraph();
	f = 0.0;
	Res = A.edmonskarp(G,f);
	if (f == m) {
		cout << "B" << endl;
		printSol(n, m, Res);
		return 0;
	}
	else {
		G.UpdateGraph2(m);
		//G.printgraph();
		f = 0.0;
		Res = A.edmonskarp(G,f);
		if (f == m){
			cout << "C" << endl;
			printSol(n, m, Res);
		}
		else {
			cout << "D" << endl;
		}
	}
	return 0;
}
