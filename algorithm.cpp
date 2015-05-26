#include "graph.cpp"
#include <queue>
#include <cmath>



typedef vector< vector<float> > Matrix;


/* BFS */

class Algorithm

{

public:

	float bfsflujo(Graph& A,Matrix& F,vector<float>& P)
	{		
		int source = A.getSource();
		int sink = A.getSink();
		int tam = A.size();
		vector<float> M (tam);	
		P[source] = -2;
		M[source] = INFINITY;
		queue<int> Q;
		Q.push(source);
		while(not Q.empty()){
			int u = Q.front();
			Q.pop();
			vector <float> filaady = A.getNeighbours(u); 
			for(int i = 0; i<filaady.size(); ++i ){ //Para cada adyacente.
				int v= filaady[i];
				if ((A.weight(u,v) - F[u][v]) > 0 and P[v] == -1){ // Si C[u][v]-F[u][v] > 0 and P[v] == -1
					P[v] = u;
					M[v] = min(M[u], A.weight(u,v)-F[u][v]);
					if (v != sink ) Q.push(v);
					else return M[sink];
				}
			}
		}
		return 0;
	}

	/*  edmons karp  */


	Matrix edmonskarp(Graph& A, float& f)
	{
		f = 0;	
		Matrix F (A.size(), vector<float> (A.size()));
		vector <float> P(A.size(),-1);
		float m = bfsflujo(A,F,P);
		while (m != 0) {
			f = f + m;
			int v = A.getSink();
			while (v != A.getSource()){
				int u = P[v];
				F[u][v] = F[u][v] + m;
				F[v][u] = F[v][u] - m;
				v = u;		
			}
			m = bfsflujo(A,F,P);	
		}
		return F;
	}


	float min (float a, float b)
	{
		if (a>b) return b;
		return a;
	}
};
