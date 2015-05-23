#include "graph.cpp"
#include <queue>
#include <cmath>


//typedef vector< vector<float> > Matrix;

/*  edmons karp  */

//typedef vector< vector<float> > Matrix;

/*Matrix edmonskarp(Matrix& Ady, Matrix& Cap, int source,int sink, float& f)
{
	typedef vector< vector<float> > Matrix;
	f = 0;	
	Matrix F (Ady.size(), vector<float> (Ady.size()));
	float m;
	vector <float> P;
	//int m = bfs;
	while (m != 0) {
		f = f + m;
		int v = t;
		while (v != s){
			int u = P[v];
			F[u][v] = F[u][v] + m;
			F[v][u] = F[v][u] - m;
			v = u;		
		}
		//m = bfs	
	}
	return F;
}*/


float min (float a, float b)
{
	if (a>b) return b;
	return a;
}

/* BFS */

/*float bfs(graph& A, int source, int sink,int tam,int flujo,vector<float>& P)
{
		
	vector<float> P (tam,-1.0);
	vector<float> M (tam)	
	P[source] = -2;
	M[source] = INFINITY;
	queue<int> Q;
	Q.push(source);
	while(not Q.empty()){
		int u = Q.front();
		Q.pop();
		vector <int> filaady = A.getfila(u); 
		for(int i = 0; i<filaady.size(); ++i ){ //Para cada adyacente.
			int v= filaady[i];
			if (){ // Si C[u][v]-F[u][v] > 0 and P[v] == -1
			// P[v] = u;
			// M[v] = min(M[u], C[u][v]-F[u][v]);
			// if (v != t ) Q.push(v);
			// else return M[t];
			//}
		}
	}
	return 0;
}*/