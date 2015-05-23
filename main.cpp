#include "graph.cpp"
#include <queue>
#include <cmath>

typedef vector< vector<float> > Matrix;

void printgraph(graph& A){
	int n = A.numfilas();
	int m = A.numcolumnas();
	cout<<"------------------------------"<<endl;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			cout<<A.weight(i,j)<<" ";
		}	
		cout<<endl;
	}
	cout<<"------------------------------"<<endl;
}




/*  edmons karp  */

Matrix edmonskarp(Matrix& Ady, Matrix& Cap, int source,int sink, float& f){
	f = 0;	
	Matrix F (Ady.size(), vector<float> (Ady.size()));
	float m;
	int tam = Ady.size()+2; 	
	vector<float> P (tam,-1.0);
	//int m = bfs;
	while (m != 0) {
		f = f + m;
		int v = sink;
		while (v != source){
			int u = P[v];
			F[u][v] = F[u][v] + m;
			F[v][u] = F[v][u] - m;
			v = u;		
		}
		//m = bfs	
	}
	return F;
}


float minimo (float a, float b){
	if (a>b) return b;
	else return a;
}

float bfs(Matrix& Ady, Matrix& Cap, int source, int sink,int tam,Matrix& F,vector<float>& P){
		

	vector<float> M (tam);	
	P[source] = -2;
	M[source] = INFINITY;
	queue<int> Q;
	Q.push(source);
	while(not Q.empty()){
		int u = Q.front();
		Q.pop();
		vector <float> filaady = Ady[u]; 
		for(int i = 0; i<Ady[u].size(); ++i ){ //Para cada adyacente.
			int v= Ady[u][i];
			if (Cap[u][v]-F[u][v] > 0 and P[v] == -1){ // Si 
			 P[v] = u;
			 M[v] = minimo(M[u], Cap[u][v]-F[u][v]);
			 if (v != sink ) Q.push(v);
			 else return M[sink];
			}
		}
	}
	return 0;
}


int main() {
	int n,m;
	cin>> n >> m;
	graph A = *new graph(n,m);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			int value;
			cin>>value;
			A.addEdge(i,j,value);
		}	
	}
	
	printgraph(A);
}
