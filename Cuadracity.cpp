// IGNACIO VITORES SANCHO
// Se recorre la matriz de derecha a izquierda y de abajo a arriba. Se inicializa la ultima fila y la ultima columna al valor de la posicion 
// anterior en la fila/columna si no hay pozo y 0 si no. El valor de cada casilla de la matriz es igual a la suma del valor de la casilla de 
// abajo y la de la derecha. El resultado es el valor de la casilla inicial
#include <iostream>
#include <fstream>

#include "Matriz.h"

using namespace std;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(Matriz<char> const & datos, Matriz<int> &caminos, const int numColumnas, const int numFila) {
	for (int i = numFila - 2; i >= 0; i--){
		for (int j = numColumnas - 2; j >= 0; j--){
			if (datos[i][j] == 'P')
				caminos[i][j] = 0;
			else
				caminos[i][j] = caminos[i + 1][j] + caminos[i][j + 1];
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int filas, columnas;
	std::cin >> filas >> columnas;
	if (!std::cin) // fin de la entrada
		return false;
	Matriz<int> caminos(filas, columnas, 0);
	Matriz<char> datos(filas, columnas);
	for (int i = 0; i < filas; i++){
		for (int j = 0; j < columnas; j++){
			std::cin >> datos[i][j];
		}
	}
	if (datos[filas - 1][columnas - 1] == 'P')
		cout << 0 << endl;
	else{
		caminos[filas - 1][columnas - 1] = 1;
		for (int i = filas - 2; i >= 0; i--){
			if (datos[i][columnas - 1] == 'P')
				caminos[i][columnas - 1] = 0;
			else
				caminos[i][columnas - 1] = caminos[i + 1][columnas - 1];
		}
		for (int i = columnas - 2; i >= 0; i--){
			if (datos[filas - 1][i] == 'P')
				caminos[filas - 1][i] = 0;
			else
				caminos[filas - 1][i] = caminos[filas - 1][i + 1];

		}
		resolver(datos, caminos, columnas, filas);
		std::cout << caminos[0][0] << std::endl;
	}
	return true;
}

int main() {
	
	// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
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