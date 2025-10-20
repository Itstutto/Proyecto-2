#pragma once
#include <string>
#include <sstream>
#include "NodoEstadoCarro.h"
using namespace std;
class ListaEstados
{
private:
	NodoEstadoCarro* primero;
	NodoEstadoCarro* ultimo;
	int tam;
public:
	ListaEstados();
	~ListaEstados();
	// Getters
	NodoEstadoCarro* getPrimero();
	NodoEstadoCarro* getUltimo();
	int getTam();
	// Métodos adicionales
	bool insertarInicio(string e);
	NodoEstadoCarro* buscarEstado(string e);
	string mostrarEstados();
};

