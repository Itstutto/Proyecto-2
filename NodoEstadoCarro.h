#pragma once
#include <string>
using namespace std;


//Nodo para el estado del carro en el estacionamiento  Disponible a Alquilado, Revisi�n o a Lavado

class NodoEstadoCarro
{
private:
	string estado; // Disponible, Alquilado, Revisi�n, Lavado
	NodoEstadoCarro* sig;
public:
	NodoEstadoCarro();
	NodoEstadoCarro(string e);
	string getEstado();
	NodoEstadoCarro* getSig();
	void setEstado(string e);
	void setSig(NodoEstadoCarro* s);
};

