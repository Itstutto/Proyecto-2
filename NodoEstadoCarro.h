#pragma once
#include <string>
using namespace std;


//Nodo para el estado del carro en el estacionamiento  Disponible a Alquilado, Revisi�n o a Lavado

struct NodoEstadoCarro
{
	string estado; // Disponible, Alquilado, Revisi�n, Lavado
	NodoEstadoCarro* sig;
	NodoEstadoCarro();
	NodoEstadoCarro(string e);
};

