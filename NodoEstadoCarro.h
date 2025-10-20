#pragma once
#include <string>
using namespace std;


//Nodo para el estado del carro en el estacionamiento  Disponible a Alquilado, Revisión o a Lavado

struct NodoEstadoCarro
{
	string estado; // Disponible, Alquilado, Revisión, Lavado
	NodoEstadoCarro* sig;
	NodoEstadoCarro();
	NodoEstadoCarro(string e);
};

