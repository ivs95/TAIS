// IGNACIO VITORES SANCHO
// Se ordenan las cajas por orden segun su tiempo en un monticulo. En caso de empate se utiliza el indice para desempatar
// Cuando llega un nuevo cliente, se añade su tiempo a la caja de la cima actualizando su posicion
#include <iostream>
#include <fstream>

#include "PriorityQueue.h"


using namespace std;

//Estructura para guardar cada caja
typedef struct{
	int n; //Indice de la caja
	int tiempo; //Tiempo total de los clientes
} Caja;

bool operator < (Caja c1, Caja c2){
	if (c1.tiempo < c2.tiempo)
		return true;
	else if (c1.tiempo == c2.tiempo)
		return c1.n < c2.n;
	else return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	int numCajas, numClientes;
	cin >> numCajas >> numClientes;
	if (numCajas == 0)
		return false;
	PriorityQueue<Caja> cajas;
	Caja aux;
	for (int i = 1; i <= numCajas; i++){
		aux.n = i;
		aux.tiempo = 0;
		cajas.push(aux);
	}
	int tiempo;
	for (int i = 0; i < numClientes; i++){
		aux = cajas.top();
		cajas.pop();
		cin >> tiempo;
		aux.tiempo += tiempo;
		cajas.push(aux);
		
	}
	std::cout << cajas.top().n << endl;
	
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