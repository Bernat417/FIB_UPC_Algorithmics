#include "graph.cpp"


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
