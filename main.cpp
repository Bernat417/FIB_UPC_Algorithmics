#include "algorithm.cpp"

int main (int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage of planning: planning arg1" << endl;
		cout << "Where arg1 is either 0 or 1 to choose either:" << endl;
		cout << "    0. EdmonsKarp Algorithm" << endl;
		cout << "    1. Preflow Algorithm" << endl;
		exit(0);
	}
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n,m);
	G.readGraph(m);
	G.printgraph();
	Algorithm A = *new Algorithm();
	float f = 0.0;
	Matrix Res = A.edmonskarp(G,f);
	vector<int> sol(m);
	if (f == m)
	{
		cout<<f<<endl;		
		for (int i = 2; i < n+2; ++i){
			for (int j = n+2; j < m+n+2; ++j){
				if (Res[i][j] == 1) sol[j-(n+2)] = i;
			}
		}
		for (int i = 0; i < sol.size(); ++i) cout<<sol[i]-2;
		cout<<endl;
	}
	else {
		G.UpdateGraph(m);
		G.printgraph();
		f = 0.0;
		Res = A.edmonskarp(G,f);
		if (f == m){
			cout<<"C"<<endl;
			for (int i = 2; i < n+2; ++i){
				for (int j = n+2; j < m+n+2; ++j){
					if (Res[i][j] == 1) sol[j-(n+2)] = i;
				}
			}
			for (int i = 0; i < sol.size(); ++i) cout<<sol[i]-2;
			cout<<endl;
		}
		else {
			cout<<"D"<<endl;
		}
	}
}
