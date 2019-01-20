// IGNACIO VITORES SANCHO
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ConjuntosDisjuntos.h"// propios o los de las estructuras de datos de clase

using namespace std;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

void leerNuevaMancha(vector<string> const & datos, ConjuntosDisjuntos &sol, const int fila, const int columna, const int i, const int j){
	const vector<pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };
	for (auto d : dirs){
		int ni = i + d.first, nj = j + d.second;
		if (ni >= 0 && ni < fila && nj >= 0 && nj < columna){
			if (datos[ni][nj] == '#')
				sol.unir(i*columna + j, ni*columna + nj);
		}
	}
}

void leerMancha(vector<string> const & datos, ConjuntosDisjuntos &sol, const int fila, const int columna, const int i, const int j, vector<bool> & marcas){
	const vector<pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
	marcas[i*columna + j] = true;
	for (auto d : dirs){
		int ni = i + d.first, nj = j + d.second;
		if (ni >= 0 && ni < fila && nj >= 0 && nj < columna){
			if (datos[ni][nj] == '#' && !marcas[ni*columna + nj]){
				sol.unir(i*columna + j, ni*columna + nj);
				leerMancha(datos, sol, fila, columna, ni, nj, marcas);
			}
		}
	}
}

int leerManchas(vector<string> const & datos, ConjuntosDisjuntos &sol, const int fila, const int columna, vector<bool> & marcas){
	int retorno = 0;
	for (int i = 0; i < fila; i++){
		for (int j = 0; j < columna; j++){
			if (datos[i][j] == '#' && !marcas[i*columna+j]){
				leerMancha(datos, sol, fila, columna, i, j, marcas);
				if (retorno < sol.tam(i*columna + j))
					retorno = sol.tam(i*columna + j);
			}
		}
	}
	return retorno;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	int fila, columna;
	cin >> fila >> columna;
	if (!std::cin) // fin de la entrada
		return false;
	vector<string>datos(fila);
	std::getline(cin, datos[0]);
	for (int i = 0; i < fila; i++){
		std::getline(cin, datos[i]);
	}
	ConjuntosDisjuntos sol(fila*columna);
	vector<bool>marcas(fila*columna);
	int maxMancha = leerManchas(datos, sol, fila, columna, marcas); 
	cout << maxMancha;
	int nuevasManchas;
	cin >> nuevasManchas;
	int nfila, ncolumna;
	for (int i = 0; i < nuevasManchas; i++){
		cin >> nfila >> ncolumna;
		nfila--;
		ncolumna--;
		datos[nfila][ncolumna] = '#';
		leerNuevaMancha(datos, sol,fila,columna,nfila,ncolumna);
		if (maxMancha < sol.tam(nfila*columna + ncolumna))
			maxMancha = sol.tam(nfila*columna + ncolumna);
		cout << " " << maxMancha;
	}
	cout << endl;
	
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