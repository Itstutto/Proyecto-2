#pragma once
#include <string>
#include <sstream>
#include "SolicitudAlquiler.h"

class ListaSolicitudesContratos {
private:
	NodoSolicitud* primero;
	NodoSolicitud* ultimo;
	int tam;
public:
	ListaSolicitudesContratos();
	~ListaSolicitudesContratos();
	int getTam() const;
	bool insertarFinal(SolicitudAlquiler* s);
	SolicitudAlquiler* buscarTransaccion(const int& pos);
	string mostrarTransacciones();
	string toString() const;
};
