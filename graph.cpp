#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

typedef vector< vector<float> > Matrix;

class WeightedEdge
{
	public:
		int neighbour;
		float weight;

		WeightedEdge()
		{
			neighbour = weight = 0;
		}

		WeightedEdge(int x, float y)
		{
			neighbour = x;
			weight = y;
		}

		bool operator<(const WeightedEdge& e) const
		{
			return neighbour < e.neighbour;  //assume that you compare the record based on a
		}

		bool operator== ( const WeightedEdge &e)
		{
    		return neighbour == e.neighbour;
		}
};


class Graph

{

private:


	typedef vector <  set<WeightedEdge>  > VectorOfSets;
	VectorOfSets neighbours;
	int numPersons;
	int numTrips;
	Matrix Entrada;
	vector<float> numpersonasviaje;

public:

	Graph(int x, int y)
	{
		numPersons = x;
        numTrips = y;
		neighbours = VectorOfSets(x + y + 4, set <WeightedEdge>());
		Entrada = *new Matrix(x,vector<float>(y,0.0)); 	// Lo necesitamos guardar, porque si no encontramos una solucion valida de un tipo A o B, entonces hay que rehacer el
														// grafo para el tipo C, o sea, contamos dentro del grafo la gente con preferencia 1.
	}

	void addEdge(int x, int y, float weight)
	{
		neighbours[x].insert(WeightedEdge(y,weight));
	}

	bool conected(int x, int y)
	{
		WeightedEdge e(y,0);
		return neighbours[x].find(e) != neighbours[x].end();
	}

	float weight(int x, int y)
	{
		WeightedEdge e(y,0);
		return (*(neighbours[x].find(e))).weight;
	}

	int getneighbour(WeightedEdge x){
		return x.neighbour;
	}

	int getNumPersonas(){
		return numPersons;
	}

	float size()
	{
		return numPersons + numTrips + 4;
	}

	vector<WeightedEdge> getNeighbours(int x)
	{
		vector <WeightedEdge> v (neighbours[x].size());
		int i = 0;
		for (set<WeightedEdge>::iterator it = neighbours[x].begin(); it!= neighbours[x].end(); ++it)
		{
			v[i] = WeightedEdge ((*it).neighbour, (*it).weight);
			++i;
		}
		return v;
	}

	bool readGraph(int Cols)
	{

		int index = 2;

		//------ Para las aristas -----
		numpersonasviaje = *new vector<float>(Cols,0.0);
		vector<float> capacidadpersona(numPersons,0.0);

		//------ Para saber que tipo de solucion tenemos (hay que volverse a mirar esto)
		vector<bool> hayun3col(Cols,false);
		//int num3 = Cols;
		bool tipoA = true;

		// Tengo que leer la matriz y guardarmela por si tengo que rehacer el grafo en caso de que no encuentra una solucion de tipo A o B
		// (de C no, porque si no hay solucion para C entonces es que no existe asignacion justa).
		for (int i =0; i< numPersons; ++i){
			for (int j = 0; j < Cols; ++j) {
				float val;
				cin>>val;
				Entrada[i][j] = val;
				if (val > 0){
					++numpersonasviaje[j];
					if (val == 3){
						if (not hayun3col[j]) {
							hayun3col[j] = true;
							//--num3;
						}
						else tipoA = false;
					}
				}
			}
		}
		//if (num3 > 0) tipoA = false;
		//if (num3 != ) tipoA = false;
		// Empezamos a montar el grafo. Tenemos las personas,los viajes un source(s) y un sink(t) y ademas necesitamos un s' y un t'
		// para la transformacion de un grafo de circulacion con lower bounds a uno de max-flow.
		float value;
		float acvalue = 0.0;
		bool first = true;
		for (int i = 0; i < numPersons; ++i) {
			acvalue = 0.0;
			for (int j = 0; j < Cols; ++j){
				value = Entrada[i][j];
                //Si estoy buscando una solucion de tipo A,B (value > 1) o C (value > 0).
                //if (value > 1) acvalue += 1.0/numpersonasviaje[j];
				if (value > 0.0) acvalue += 1.0/numpersonasviaje[j];
                if(value > 2.0 or (value > 1.0 and !hayun3col[j])) {
                    cout << "Persona: " << i << " Viatge: " << j << " " << value << endl;
                    // Calculo la "capacidad" de la persona y pongo su arista de persona-viaje.
                    //acvalue += 1.0/numpersonasviaje[j];		// Ejemplo transpas:  Capacidad persona 1: S1 = 1/3+1/3+1/4.Parte inferior de lS1 = 0 y la superior es uS1=1.
                    addEdge(i + 2,numPersons + 2 +j,1.0);	// Capacidad = parte superior de la capacidad menos parte inferior de la capacidad. La diferencia es siempre 1.
                }
				if (first){
		            addEdge(numPersons + 2+ j, numPersons + numTrips + 2, 1.0); //Anado todas las aristas de viajes a t (no a t' ).
				}
			}
			first = false;
			capacidadpersona[i] = acvalue;
			cout << "Persona: " << i << " acvalue: " << acvalue << endl;
            ++index;
			addEdge(1, i + 2,ceil(capacidadpersona[i]) - floor(capacidadpersona[i]));
		}
		addEdge(numPersons+numTrips+2,1,INFINITY); // Anado la arista del reflow.
		addEdge(numPersons+numTrips+2,numPersons+numTrips+3,Cols); //Arista de t a t'
		int sumabajo,sumalto,bajo,alto;
		sumabajo = sumalto = 0;
		// Aqui pongo todas las aristas que conectan s' con las personas suministrando su demanda.
		// Y calculo la suma total de las partes inferiores y las superiores.
		for (int i = 0; i < numPersons; ++i){
			bajo = floor(capacidadpersona[i]);	// Trunco el valor para tener la cota inferior y luego la superior.
			alto = ceil(capacidadpersona[i]);
			sumabajo += bajo;
			sumalto += alto;
			addEdge(0,i+2,bajo);
			cout << "Persona: " << i << " bajo: " << bajo << " alto: " << alto << endl;
		}
		// Conecto s con s' dandole como capacidad la diferencia entre la suma de partes superiores menos inferiores
		// que es la cantidad que debe repartir edmonds-karp para proporcionarme la asignacion justa.
		addEdge(0,1,sumalto-sumabajo);
		cout << "sumalto: " << sumalto << " sumabajo: " << sumabajo << endl;
		return tipoA;
	}

	void UpdateGraph1(int Cols){
		neighbours = VectorOfSets(numPersons + numTrips + 4, set <WeightedEdge>());

		int index = 2;

		//------ Para las aristas -----
		vector<float> capacidadpersona(numPersons,0.0);
		float value;
		float acvalue = 0.0;
		bool first = true;
		for (int i = 0; i < numPersons; ++i) {
			acvalue = 0.0;
			for (int j = 0; j < Cols; ++j){
				value = Entrada[i][j];
				if (value > 0.0) acvalue += 1.0/numpersonasviaje[j];
				if(value > 1.0) {
                    //Si estoy buscando una solucion de tipo A,B (value > 1) o C (value > 0).
                    // Calculo la "capacidad" de la persona y pongo su arista de persona-viaje.
					// Ejemplo transpas:  Capacidad persona 1: S1 = 1/3+1/3+1/4.Parte inferior de lS1 = 0 y la superior es uS1=1.
                    addEdge(i + 2,numPersons + 2 +j,1.0);	// Capacidad = parte superior de la capacidad menos parte inferior de la capacidad. La diferencia es siempre 1.
				}
				if (first){
		            addEdge(numPersons + 2+ j, numPersons + numTrips + 2, 1.0); //Anado todas las aristas de viajes a t (no a t' ).
				}
			}
			first = false;
			capacidadpersona[i] = acvalue;
            ++index;
			addEdge(1, i + 2,ceil(capacidadpersona[i]) - floor(capacidadpersona[i]));
		}
		addEdge(numPersons+numTrips+2,1,INFINITY); // Anado la arista del reflow.
		addEdge(numPersons+numTrips+2,numPersons+numTrips+3,Cols);
		int sumabajo,sumalto,bajo,alto;
		sumabajo = sumalto = 0;
		// Aqui pongo todas las aristas que conectan s' con las personas suministrando su demanda.
		// Y calculo la suma total de las partes inferiores y las superiores.
		//neighbours[0].clear();
		for (int i = 0; i < numPersons; ++i){
			bajo = floor(capacidadpersona[i]);	// Trunco el valor para tener la cota inferior y luego la superior.
			alto = ceil(capacidadpersona[i]);
			sumabajo += bajo;
			sumalto += alto;
			addEdge(0,i+2,bajo);
		}
		// Conecto s con s' dandole como capacidad la diferencia entre la suma de partes superiores menos inferiores
		// que es la cantidad que debe repartir edmonds-karp para proporcionarme la asignacion justa.
		addEdge(0,1,sumalto-sumabajo);
	}

	void UpdateGraph2(int Cols){
		neighbours = VectorOfSets(numPersons + numTrips + 4, set <WeightedEdge>());
		int index = 2;

		//------ Para las aristas -----
		vector<float> capacidadpersona(numPersons,0.0);
		float value;
		float acvalue = 0.0;
		bool first = true;
		for (int i = 0; i < numPersons; ++i) {
			acvalue = 0.0;
			for (int j = 0; j < Cols; ++j){
				value = Entrada[i][j];
                //Si estoy buscando una solucion de tipo A,B (value > 1) o C (value > 0).
                if(value > 0.0) {
                    // Calculo la "capacidad" de la persona y pongo su arista de persona-viaje.
                    acvalue += 1.0/numpersonasviaje[j];		// Ejemplo transpas:  Capacidad persona 1: S1 = 1/3+1/3+1/4.Parte inferior de lS1 = 0 y la superior es uS1=1.
                    addEdge(i + 2,numPersons + 2 +j,1.0);	// Capacidad = parte superior de la capacidad menos parte inferior de la capacidad. La diferencia es siempre 1.
                }
				if (first){
		            addEdge(numPersons + 2+ j, numPersons + numTrips + 2, 1.0); //Anado todas las aristas de viajes a t (no a t' ).
				}
			}
			first = false;
			capacidadpersona[i] = acvalue;
            ++index;
			addEdge(1, i + 2,ceil(capacidadpersona[i]) - floor(capacidadpersona[i]));
		}
		addEdge(numPersons+numTrips+2,1,INFINITY); // Anado la arista del reflow.
		addEdge(numPersons+numTrips+2,numPersons+numTrips+3,Cols);
		int sumabajo,sumalto,bajo,alto;
		sumabajo = sumalto = 0;
		// Aqui pongo todas las aristas que conectan s' con las personas suministrando su demanda.
		// Y calculo la suma total de las partes inferiores y las superiores.
		//neighbours[0].clear();
		for (int i = 0; i < numPersons; ++i){
			bajo = floor(capacidadpersona[i]);	// Trunco el valor para tener la cota inferior y luego la superior.
			alto = ceil(capacidadpersona[i]);
			sumabajo += bajo;
			sumalto += alto;
			addEdge(0,i+2,bajo);
		}
		// Conecto s con s' dandole como capacidad la diferencia entre la suma de partes superiores menos inferiores
		// que es la cantidad que debe repartir edmonds-karp para proporcionarme la asignacion justa.
		addEdge(0,1,sumalto-sumabajo);
	}


	void printgraph()
	{
		for (int i = 0; i < numPersons + numTrips + 4; ++i)
		{
			cout << "----------------------------" << i <<"----------------------------" << endl;
			for (set<WeightedEdge>::iterator it = neighbours[i].begin(); it!= neighbours[i].end(); ++it)
				cout << "neighbour: " << (*it).neighbour << " weight: " << (*it).weight << endl;

			cout<<endl;
		}
	}



};
