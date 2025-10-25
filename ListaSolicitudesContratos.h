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
	bool insertarFinal(SolicitudAlquiler* s);
	SolicitudAlquiler* buscarTransaccion(const string& codigo);
	string mostrarTransacciones();
};
