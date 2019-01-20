// IGNACIO VITORES SANCHO
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#include "GrafoDirigidoValorado.h" // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

using namespace std;

class Navegador{
public:
	Navegador(GrafoDirigidoValorado<int> const & datos) : aristas(datos.V()), distTo(datos.V(), numeric_limits<int>::max()), pq(datos.V()), posible(false){
		distTo[0] = 0;
		pq.push(0, 0);
		while (!pq.empty()){
			int v = pq.top().elem;
			pq.pop();
			for (AristaDirigida<int> a : datos.ady(v)){
				relajar(a);
			}
		}
		if (distTo[datos.V() - 1] != numeric_limits<int>::max())
			posible = true;
	}

	int tiempo(int pos) {return distTo[pos]; }
	bool hayCamino(){ return posible; };

private:
	vector<AristaDirigida<int>> aristas;
	vector<int> distTo;
	IndexPQ<int> pq;
	bool posible;

	void relajar(AristaDirigida<int> const &a){
		int ini = a.from(), fin = a.to();
		if (distTo[fin] > distTo[ini] + a.valor()){
			distTo[fin] = distTo[ini] + a.valor();
			aristas[fin] = a;
			pq.update(fin, distTo[fin]);
		}
	}
	
};



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	int numPaginas;
	cin >> numPaginas;
	if (numPaginas == 0)
		return false;
	GrafoDirigidoValorado<int> datos(numPaginas);
	vector<int> cargas(numPaginas);
	for (int i = 0; i < numPaginas; i++){
		cin >> cargas[i];
	}
	int numEnlaces;
	cin >> numEnlaces;
	int ini, fin, tiempo;
	for (int i = 0; i < numEnlaces; i++){
		cin >> ini >> fin >> tiempo;
		ini--;
		fin--;
		AristaDirigida<int> arista(ini, fin, cargas[ini] + tiempo);
		datos.ponArista(arista);
	}
	bool posible = false;
	Navegador nav(datos);
	if (nav.hayCamino()){
		cout << (nav.tiempo(numPaginas-1) + cargas[numPaginas-1]) << endl;
	}
	else
		cout << "IMPOSIBLE" << endl;
	
	return true;
}

int main() {
	
	// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif
	
	while(resuelveCaso());
	
	// para dejar todo como estaba al principio
	#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
	#endif
	return 0;
}