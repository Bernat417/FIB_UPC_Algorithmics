#include "graph.cpp"
#include <queue>







/* BFS */

class Algorithm

{

public:

	Algorithm(){

	}
	
	//--------------- EDMONDS-KARP ----------------//

	/*BFS*/

	float bfsflujo(Graph& A,Matrix& F,vector<float>& P)
	{	
		P = *new vector<float>(A.size(),-1);	
		int sink = A.size()-1;
		int tam = A.size();
		vector<float> M (tam);	
		P[0] = -2;
		M[0] = INFINITY;
		queue<int> Q;
		Q.push(0);
		while(not Q.empty()){
			int u = Q.front();
			Q.pop();
			vector <WeightedEdge> filaady = A.getNeighbours(u); 
			for(int i = 0; i<filaady.size(); ++i ){ 
				int v= A.getneighbour(filaady[i]);
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
		Matrix F (A.size(), vector<float> (A.size(),0));
		vector <float> P(A.size(),-1);
		float m = bfsflujo(A,F,P);
		while (m != 0) {
			f = f + m;
			int v = A.size()-1;
			while (v != 0){
				int u = P[v];
				F[u][v] = F[u][v] + m;
				F[v][u] = F[v][u] - m;
				v = u;		
			}
			m = bfsflujo(A,F,P);	
		}
		cout<<endl;
		return F;
	}


	float min (float a, float b)
	{
		if (a>b) return b;
		return a;
	}

	//--------------- PUSH-RELABEL ----------------//

//links con info (borrarlo luego)
//http://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
//https://sites.google.com/site/indy256/algo/preflow
//http://cophy-wiki.informatik.uni-koeln.de/index.php/The_push-relabel_algorithm

	Matrix preflow(Graph& A,float& f){
		int n = A.getNumPersonas();
		vector<float> height(n,0);		// Or "label distance".
		vector<float> maxheight(n,0);	// Or "max label distance".
		vector<float> exceso(n,0);
		height[0] = n;
		Matrix F(A.size(), vector<float>(A.size(),0));
		vector<WeightedEdge> aux = A.getNeighbours(0);
		for (int i = 0; i < aux.size(); ++i){
			float w = A.weight(0,i); 
			F[0][i] = w;
			F[i][0] = -w;
			exceso[i] = w;
		}
		for (int a = 0; a< n; ++a){  // Hasta n? no estoy muy seguro.
			if (a == 0){
				for (int i = 0; i < n; ++i){
					if ((i !=0) and (i != A.size()-1) and exceso[i]>0){
						if (a != 0 and height[i] > height[maxheight[0]]) a = 0;
						maxheight[++a] = i;						
					}
				}
			}
			if (a == 0)	break;
			while (a != 0){
				int i = maxheight[a-1];
				bool push = false;
				for (int j = 0; j < n && exceso[i]!=0; ++j){
					if (height[i]==height[j] +1 and A.weight(i,j)- F[i][j] > 0){
						int resto = min(A.weight(i,j)- F[i][j],exceso[i]);
						F[i][j] += resto;
						F[j][i] = resto;
						exceso[i] -= resto;
						exceso[j] += resto;
						if (exceso[i] == 0) --a;
						push = true;
					}
				}
				if (not push){
					height[i] = INFINITY;
					for (int z =0; z < n; ++z){
						if (height[i] > height[z] +1 and A.weight(i,z)- F[i][z] > 0){
							height[i] = height[z] +1;
						}
					}
					if (height[i] > height[maxheight[0]]){
						a = 0;
						break;
					}
				}
			}
		}
		for (int i = 0; i < n; ++i){
			f += F[0][i]; 
		}
		return F;
	}
































};
