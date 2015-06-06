#include "algorithm.cpp"

int main (int argc, char *argv[]) {
	
	ofstream file;
	file.open ("solucio.txt");
	
	int n, m;
	cin >> n >> m;
	Graph G = *new Graph(n,m);
	bool tipoA = G.readGraph(m);
	//G.printgraph();
	Algorithm A = *new Algorithm();
	float f = 0.0;
	Matrix Res;
	vector<int> sol(m);
	if (tipoA) {
		Res = A.edmonskarp(G,f);
		if (f == m) {
			file << "A" << endl;
			//file<<f<<endl;		
			for (int i = 2; i < n+2; ++i){
				for (int j = n+2; j < m+n+2; ++j){
					if (Res[i][j] == 1) sol[j-(n+2)] = i;
				}
			}
			file << sol[0]-2;
			for (int i = 1; i < sol.size(); ++i) file << " " << sol[i]-2;
			file<<endl;
			file.close();
			return 0;
		}
	}
	G.UpdateGraph1(m);
	//G.printgraph();
	f = 0.0;
	Res = A.edmonskarp(G,f);
	if (f == m) {
		file << "B" << endl;
		//file<<f<<endl;		
		for (int i = 2; i < n+2; ++i){
			for (int j = n+2; j < m+n+2; ++j){
				if (Res[i][j] == 1) sol[j-(n+2)] = i;
			}
		}
		file << sol[0]-2;
			for (int i = 1; i < sol.size(); ++i) file << " " << sol[i]-2;
		file<<endl;
		file.close();
		return 0;
	}
	else {
		G.UpdateGraph2(m);
		//G.printgraph();
		f = 0.0;
		Res = A.edmonskarp(G,f);
		if (f == m){
			file<<"C"<<endl;
			for (int i = 2; i < n+2; ++i){
				for (int j = n+2; j < m+n+2; ++j){
					if (Res[i][j] == 1) sol[j-(n+2)] = i;
				}
			}
			file << sol[0]-2;
			for (int i = 1; i < sol.size(); ++i) file << " " << sol[i]-2;
			file<<endl;
		}
		else {
			file<<"D"<<endl;
		}
	}
	file.close();
	return 0;
}
