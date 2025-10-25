#include "ListaSolicitudesContratos.h"

ListaSolicitudesContratos::ListaSolicitudesContratos() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaSolicitudesContratos::~ListaSolicitudesContratos() {
	NodoSolicitud* a = primero;
	while (a) {
		NodoSolicitud* s = a->getSig();
		delete a->getDato();
		delete a;
		a = s;
	}
}

bool ListaSolicitudesContratos::insertarFinal(SolicitudAlquiler* s) {
	if (!s) return false;
	NodoSolicitud* n = new NodoSolicitud(s);
	if (!primero) {
		primero = ultimo = n;
	} else {
		ultimo->setSig(n);
		ultimo = n;
	}
	tam++;
	return true;
}

SolicitudAlquiler* ListaSolicitudesContratos::buscarTransaccion(const string& codigo) {
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getCodigoTransaccion() == codigo) return a->getDato();
		a = a->getSig();
	}
	return nullptr;
}

string ListaSolicitudesContratos::mostrarTransacciones() {
	stringstream ss;
	ss << "Transacciones:" << "\n";
	NodoSolicitud* a = primero;
	while (a) {
		ss << "- " << a->getDato()->toResumen() << "\n";
		a = a->getSig();
	}
	return ss.str();
}
