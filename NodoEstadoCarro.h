#pragma once
#include <string>
using namespace std;


//Nodo para el estado del carro en el estacionamiento  Disponible a Alquilado, Revisión o a Lavado

class NodoEstadoCarro
{
private:
	string estado; // Disponible, Alquilado, Revisión, Lavado
	NodoEstadoCarro* sig;
public:
	NodoEstadoCarro();
	NodoEstadoCarro(string e);
	string getEstado();
	NodoEstadoCarro* getSig();
	void setEstado(string e);
	void setSig(NodoEstadoCarro* s);
};

