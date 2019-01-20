//IGNACIO VITORES SANCHO
// Se ordenan las peliculas por hora a la que terminan. Se recorre todo el array si no se llega a la hora final (expresada en minutos)
// Se inicializa la hora de la ultima pelicula vista a las 0. Si al recorrer el array la pelicula comienza despues de la ultima pelicula
// Se actualiza la hora de la ultima pelicula = (fin pelicula actual + 10) y se incrementa el nº de peliculas vistas
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

//Estructura para almacenar la informacion de cada pelicula
typedef struct{
	int duracion; //Duracion de la pelicula
	int horaFin; //Hora a la que termina la pelicula

} pelicula;

using namespace std;


bool ordenar(pelicula p1, pelicula p2){
	if (p1.horaFin < p2.horaFin)
		return true;
	else if (p1.horaFin == p2.horaFin)
		return p1.duracion <= p2.duracion;
	else return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	
	int numPelis;
	cin >> numPelis;
	
	if (numPelis == 0)
		return false;
	vector<pelicula> peliculas(numPelis);
	pelicula peli;
	int hora;
	int minuto;
	char aux;
	for (int i = 0; i < numPelis; i++){
		cin >> hora >> aux >> minuto >> peli.duracion;
		peli.horaFin = peli.duracion + hora * 60 + minuto;
		peliculas[i] = peli;
	}
	sort(peliculas.begin(), peliculas.end(), ordenar);
	int horaAct = 0;
	int i = 0;
	int numeroPelis = 0;
	while (horaAct < 1440 && i < peliculas.size()){
		if (horaAct <= peliculas[i].horaFin - peliculas[i].duracion){
			horaAct = peliculas[i].horaFin + 10;
			numeroPelis++;
		}
		i++;
	}
	cout << numeroPelis << endl;
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