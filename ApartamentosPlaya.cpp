// IGNACIO VITORES SANCHO
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


typedef struct{
	int ini;
	int fin;
} Apartamento;

using namespace std;

bool comparador(Apartamento i, Apartamento j){
	if (i.fin < j.fin)
		return true;
	else if (i.fin == j.fin)
		return i.ini >= j.ini;
	else return false;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	int numApartamentos;
	cin >> numApartamentos;
	if (numApartamentos == 0)
		return false;
	vector<Apartamento> datos(numApartamentos);
	Apartamento aux;
	for (int i = 0; i < numApartamentos; i++){
		cin >> aux.ini >> aux.fin;
		datos[i] = aux;
	}
	sort(datos.begin(), datos.end(), comparador);
	int tunel = -1;
	int numTuneles = 0;
	for (int i = 0; i < numApartamentos; i++){
		if (tunel < datos[i].ini || tunel + 1 > datos[i].fin){
			tunel = datos[i].fin - 1;
			numTuneles++;
		}
	}
	std::cout << numTuneles << std::endl;
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