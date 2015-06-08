#include "algorithm.cpp"

void printSol (const int& n, const int& m, const Matrix& Res, char type) {
	cout << type << endl;
	vector<int> sol(m);
	
	for (int i = 2; i < n+2; ++i)
		for (int j = n+2; j < m+n+2; ++j)
			if (Res[i][j] == 1) sol[j-(n+2)] = i;

	cout << sol[0]-2;
	
	for (int i = 1; i < sol.size(); ++i) 
		cout << " " << sol[i]-2;
	
	cout << endl;
}

int main (int argc, char *argv[]) {
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n,m);
	bool personaneg;
	bool tipoA = G.readGraph(personaneg);
	//G.printgraph();
	Algorithm A = *new Algorithm();
	float f = 0.0;
	Matrix Res;

	if (not personaneg) 
	{
		if (tipoA) 
		{
			Res = A.edmonskarp(G,f);
			//G.printgraph();
			if (f == m) printSol(n, m, Res, 'A');	
		}
		else 
		{
			G.UpdateGraph(1);
			//G.printgraph();
			f = 0.0;
			Res = A.edmonskarp(G,f);
			if (f == m)printSol(n, m, Res, 'B');
		}
	}
	else {
		G.UpdateGraph(2);
		//G.printgraph();
		f = 0.0;
		Res = A.edmonskarp(G,f);
		if (f == m) printSol(n, m, Res, 'C');
		else cout << "D" << endl;
	}
}
